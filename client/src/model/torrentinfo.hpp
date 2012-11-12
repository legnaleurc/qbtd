#ifndef QBTD_MODEL_TORRENTINFO_HPP
#define QBTD_MODEL_TORRENTINFO_HPP

#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace model {

class TorrentInfo {
public:
	explicit TorrentInfo( const QVariantMap & data );
	TorrentInfo( const TorrentInfo & that );
	TorrentInfo & operator =( const TorrentInfo & that );
	TorrentInfo( TorrentInfo && that );
	TorrentInfo & operator =( TorrentInfo && that );

	QByteArray & infoHash();
	const QByteArray & infoHash() const;
	QString & name();
	const QString & name() const;
	qreal & progress();
	qreal progress() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif
