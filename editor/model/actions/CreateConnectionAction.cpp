#include "CreateConnectionAction.h"

#include "../PoolOperators.h"
#include "../ModelRoot.h"
#include "../objects/Connection.h"

using namespace AxiomModel;

CreateConnectionAction::CreateConnectionAction(const QUuid &uuid, const QUuid &parentUuid, const QUuid &controlA,
                                               const QUuid &controlB, AxiomModel::ModelRoot *root)
    : Action(ActionType::CREATE_CONNECTION, root), uuid(uuid), parentUuid(parentUuid), controlA(controlA),
      controlB(controlB) {
}

std::unique_ptr<CreateConnectionAction> CreateConnectionAction::create(const QUuid &uuid, const QUuid &parentUuid,
                                                                       const QUuid &controlA, const QUuid &controlB,
                                                                       AxiomModel::ModelRoot *root) {
    return std::make_unique<CreateConnectionAction>(uuid, parentUuid, controlA, controlB, root);
}

std::unique_ptr<CreateConnectionAction> CreateConnectionAction::create(const QUuid &parentUuid, const QUuid &controlA,
                                                                       const QUuid &controlB,
                                                                       AxiomModel::ModelRoot *root) {
    return create(QUuid::createUuid(), parentUuid, controlA, controlB, root);
}

std::unique_ptr<CreateConnectionAction> CreateConnectionAction::deserialize(QDataStream &stream,
                                                                            AxiomModel::ModelRoot *root) {
    QUuid uuid;
    stream >> uuid;
    QUuid parentUuid;
    stream >> parentUuid;
    QUuid controlA;
    stream >> controlA;
    QUuid controlB;
    stream >> controlB;

    return std::make_unique<CreateConnectionAction>(uuid, parentUuid, controlA, controlB, root);
}

void CreateConnectionAction::serialize(QDataStream &stream) const {
    Action::serialize(stream);
    stream << uuid;
    stream << parentUuid;
    stream << controlA;
    stream << controlB;
}

bool CreateConnectionAction::forward(bool) {
    root()->pool().registerObj(Connection::create(uuid, parentUuid, controlA, controlB, root()));
    return true;
}

bool CreateConnectionAction::backward() {
    find(root()->connections(), uuid)->remove();
    return true;
}