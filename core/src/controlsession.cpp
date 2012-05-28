#include "controlsession_p.hpp"

#include <QtNetwork/QLocalSocket>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtCore/QRegExp>

using qbtd::control::ControlSession;

ControlSession::Private::Private( QLocalSocket * socket ):
socket( socket ),
engine( new QScriptEngine( this ) ) {
	this->connect( socket, SIGNAL( connected() ), SLOT( onConnected() ) );
	this->connect( this->socket, SIGNAL( disconnected() ), SLOT( onDisconnected() ) );
}

void ControlSession::Private::onDisconnected() {
	QMetaObject::invokeMethod( this->socket, "deleteLater" );

	emit this->disconnected();
}

void ControlSession::Private::onConnected() {
	this->connect( this->socket, SIGNAL( readyRead() ), SLOT( onHeaderReceived() ) );
	this->socket->write( "=0\n" );
}

void ControlSession::Private::onHeaderReceived() {
	this->socket->disconnect( SIGNAL( readyRead() ), this, SLOT( onHeaderReceived() ) );
	QTextStream sin( this->socket );
	QString line = sin.readLine();
	if( line != "=0" ) {
		// TODO error report and close socket
		this->socket->close();
		return;
	}
	this->connect( this->socket, SIGNAL( readyRead() ), SLOT( onCommandReceived() ) );
	emit this->connected();
}

void ControlSession::Private::onCommandReceived() {
	QTextStream sin( this->socket );
	QString line = sin.readLine();

	QRegExp pattern( "=(\\d+)" );
	if( pattern.exactMatch( line ) ) {
		// protocol version
		if( pattern.cap( 1 ) != "0" ) {
			// version mismatch
			return;
		}
		this->socket->write( QString( "=%1\n" ).arg( pattern.cap( 1 ) ).toUtf8() );
		return;
	}

	QString json = QString::fromUtf8( QByteArray::fromBase64( line.toUtf8() ) );
	this->engine->globalObject().setProperty( "tmp", json );
	QScriptValue v = this->engine->evaluate( "JSON.parse( tmp );" );
	this->engine->globalObject().setProperty( "tmp", this->engine->nullValue() );
	QVariantMap map = v.toVariant().toMap();

	// TODO determine this is a request or response
}

ControlSession::ControlSession():
p_( new Private( new QLocalSocket( this ) ) ) {
}

ControlSession::ControlSession( QLocalSocket * socket ):
p_( new Private( socket ) ) {
	this->connect( this->p_.get(), SIGNAL( disconnected() ), SIGNAL( disconnected() ) );
	this->connect( this, SIGNAL( connected() ), SIGNAL( connected() ) );
}

void ControlSession::close() {
	this->p_->socket->close();
}

void ControlSession::connectToHost( const QString & path ) {
	this->p_->socket->connectToServer( path );
}
