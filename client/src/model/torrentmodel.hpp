#ifndef QBTD_MODEL_TORRENTMODEL_HPP
#define QBTD_MODEL_TORRENTMODEL_HPP

#include <QtCore/QAbstractItemModel>

#include <memory>

namespace qbtd {
namespace model {

class TorrentInfo;

class TorrentModel: public QAbstractItemModel {
public:
	explicit TorrentModel( QObject * parent );

	virtual int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual QModelIndex index( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	virtual QModelIndex parent( const QModelIndex & index ) const;
	virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;

	void addTorrent( const TorrentInfo & torrent );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif
