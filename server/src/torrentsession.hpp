#ifndef TORRENTSESSION_HPP
#define TORRENTSESSION_HPP

#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace torrent {

class TorrentSession {
public:
	static void initialize();
	static TorrentSession & instance();

	void addTorrent( const QByteArray & data );
	QVariantList listTorrent() const;

private:
	TorrentSession();
	~TorrentSession();
	TorrentSession( const TorrentSession & );
	TorrentSession & operator =( const TorrentSession & );
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif
