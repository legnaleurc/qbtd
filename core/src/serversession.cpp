#include "serversession_p.hpp"
#include "localsessionsocket.hpp"

#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtCore/QRegExp>

using qbtd::control::ServerSession;
using qbtd::control::SessionSocket;

ServerSession::Private::Private( SessionSocket * socket ):
QObject(),
socket( socket ),
engine( new QScriptEngine( this ) ) {
	this->connect( this->socket, SIGNAL( readyRead() ), SLOT( onHeaderReceived() ) );
	this->connect( this->socket, SIGNAL( disconnected() ), SLOT( onDisconnected() ) );
}

void ServerSession::Private::onDisconnected() {
	QMetaObject::invokeMethod( this->socket, "deleteLater" );

	emit this->disconnected();
}

void ServerSession::Private::onHeaderReceived() {
	this->socket->disconnect( SIGNAL( readyRead() ), this, SLOT( onHeaderReceived() ) );
	QTextStream sin( this->socket );
	QString line = sin.readLine();
	if( line != "=0" ) {
		// TODO error report and close socket
		this->socket->close();
		return;
	}
	this->connect( this->socket, SIGNAL( readyRead() ), SLOT( onCommandReceived() ) );
	// TODO set state to OK
}

void ServerSession::Private::onCommandReceived() {
	QTextStream sin( this->socket );
	QString line = sin.readLine();

	QString json = QString::fromUtf8( QByteArray::fromBase64( line.toUtf8() ) );
	this->engine->globalObject().setProperty( "tmp", json );
	QScriptValue v = this->engine->evaluate( "JSON.parse( tmp );" );
	this->engine->globalObject().setProperty( "tmp", this->engine->nullValue() );
	QVariantMap map = v.toVariant().toMap();

	// TODO determine this is a request or response
}

ServerSession::ServerSession( QLocalSocket * socket, QObject * parent ):
QObject( parent ),
p_( new Private( new LocalSessionSocket( socket ) ) ) {
}

ServerSession::ServerSession( QTcpSocket * socket, QObject * parent ):
QObject( parent ),
p_( new Private( nullptr ) ) {
}

void ServerSession::close() {
}
