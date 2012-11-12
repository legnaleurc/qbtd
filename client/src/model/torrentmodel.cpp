#include "torrentmodel_p.hpp"

using qbtd::model::TorrentModel;
using qbtd::model::TorrentInfo;

TorrentModel::Private::Private():
torrents() {
}

TorrentModel::TorrentModel( QObject * parent ):
QAbstractItemModel( parent ),
p_( new Private ) {
}

int TorrentModel::columnCount( const QModelIndex & parent ) const {
	return parent.isValid() ? 0 : 2;
}

QVariant TorrentModel::data( const QModelIndex & index, int role ) const {
	if( role != Qt::DisplayRole ) {
		return QVariant();
	}
	if( index.parent().isValid() ) {
		return QVariant();
	}
	const auto & torrent = this->p_->torrents.at( index.row() );
	switch( index.column() ) {
	case 0:
		return torrent.name();
	case 1:
		return torrent.progress();
	default:
		return QVariant();
	}
}

QVariant TorrentModel::headerData( int section, Qt::Orientation orientation, int role ) const {
	if( role != Qt::DisplayRole || orientation != Qt::Horizontal ) {
		return this->QAbstractItemModel::headerData( section, orientation, role );
	}
	switch( section ) {
	case 0:
		return QObject::tr( "Name" );
	case 1:
		return QObject::tr( "Progress" );
	default:
		return QVariant();
	}
}

QModelIndex TorrentModel::index( int row, int column, const QModelIndex & parent ) const {
	if( parent.isValid() ) {
		return QModelIndex();
	}
	auto & torrent = this->p_->torrents[row];
	switch( column ) {
	case 0:
		return this->createIndex( row, column, &torrent.name() );
	case 1:
		return this->createIndex( row, column, &torrent.progress() );
	default:
		return QModelIndex();
	}
}

QModelIndex TorrentModel::parent( const QModelIndex & index ) const {
	return QModelIndex();
}

int TorrentModel::rowCount( const QModelIndex & parent ) const {
	return parent.isValid() ? 0 : this->p_->torrents.size();
}

void TorrentModel::addTorrent( const TorrentInfo & torrent ) {
	this->beginInsertRows( QModelIndex(), this->rowCount(), this->rowCount() );
	this->p_->torrents.push_back( torrent );
	this->endInsertRows();
}
