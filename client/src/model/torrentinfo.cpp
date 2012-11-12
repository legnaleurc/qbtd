#include "torrentinfo_p.hpp"

using qbtd::model::TorrentInfo;

TorrentInfo::Private::Private( const QVariantMap & data ):
infoHash( data.value( "info_hash" ).toByteArray() ),
name( data.value( "name" ).toString() ),
progress( data.value( "progress" ).toReal() ) {
}

TorrentInfo::TorrentInfo( const QVariantMap & data ):
p_( new Private( data ) ) {
}

TorrentInfo::TorrentInfo( const TorrentInfo & that ):
p_( new Private( *that.p_ ) ) {
}

TorrentInfo & TorrentInfo::operator =( const TorrentInfo & that ) {
	if( this != &that ) {
		*this->p_ = *that.p_;
	}
	return *this;
}

TorrentInfo::TorrentInfo( TorrentInfo && that ):
p_( std::move( that.p_ ) ) {
}

TorrentInfo & TorrentInfo::operator =( TorrentInfo && that ) {
	this->p_.swap( that.p_ );
	return *this;
}

QByteArray & TorrentInfo::infoHash() {
	return this->p_->infoHash;
}

const QByteArray & TorrentInfo::infoHash() const {
	return this->p_->infoHash;
}

QString & TorrentInfo::name() {
	return this->p_->name;
}

const QString & TorrentInfo::name() const {
	return this->p_->name;
}

qreal & TorrentInfo::progress() {
	return this->p_->progress;
}

qreal TorrentInfo::progress() const {
	return this->p_->progress;
}
