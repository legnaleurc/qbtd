#ifndef TORRENTSESSION_HPP
#define TORRENTSESSION_HPP

#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace torrent {

class TorrentSession: public QObject {
	Q_OBJECT
public:
	static void initialize();
	static TorrentSession & instance();

	void addTorrent( const QByteArray & data );
	void addTorrent( const QUrl & url );
	QVariantList listTorrent() const;

signals:
	void error( const QString & message );

private:
	TorrentSession();
	virtual ~TorrentSession();
	TorrentSession( const TorrentSession & );
	TorrentSession & operator =( const TorrentSession & );
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif
