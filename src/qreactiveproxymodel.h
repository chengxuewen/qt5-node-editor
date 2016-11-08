#pragma once

#include <QtCore/QIdentityProxyModel>

class QReactiveProxyModelPrivate;

/**
 * Listen to index changes and forward them to another index setData.
 * It wraps the model so the drag and drop events can be interpreted as socket
 * connections rather than whatever they were meant to be.
 *
 * This model also create and expose a submodel of all the active connections.
 *
 * This is used to implement reactive programming components such as
 * spreadsheets, pipe and filter or node based editing.
 * 
 * All connections has to be from the same model. This could be fixed later.
 */
class QReactiveProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit QReactiveProxyModel(QObject* parent = Q_NULLPTR);
    virtual ~QReactiveProxyModel();

    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                int row, int column, const QModelIndex &parent) const override;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                int row, int column, const QModelIndex &parent) override;
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;
    virtual Qt::DropActions supportedDropActions() const override;
    virtual Qt::DropActions supportedDragActions() const override;
    virtual void setSourceModel(QAbstractItemModel *sourceModel) override;
    virtual QStringList mimeTypes() const override;
    virtual Qt::ItemFlags flags(const QModelIndex &idx) const override;

    void addConnectedRole(int role);
    QVector<int> connectedRoles() const;

    QAbstractItemModel *connectionsModel() const;

    bool connectIndices(const QModelIndex& source, const QModelIndex& destination); //TODO add roles
    bool areConnected(const QModelIndex& source, const QModelIndex& destination) const; //TODO add roles

    QList<QModelIndex> sendTo(const QModelIndex& source) const;
    QList<QModelIndex> receiveFrom(const QModelIndex& destination) const;

private:
    QReactiveProxyModelPrivate* d_ptr;
    Q_DECLARE_PRIVATE(QReactiveProxyModel)
};
