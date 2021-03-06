#include "HistoryList.h"

#include "editor/compiler/interface/Transaction.h"

using namespace AxiomModel;

HistoryList::HistoryList(CompileApplyer applyer) : applyCompile(std::move(applyer)) {}

HistoryList::HistoryList(size_t stackPos, std::vector<std::unique_ptr<AxiomModel::Action>> stack,
                         AxiomModel::HistoryList::CompileApplyer applyer)
    : _stackPos(stackPos), _stack(std::move(stack)), applyCompile(std::move(applyer)) {}

void HistoryList::append(std::unique_ptr<AxiomModel::Action> action, bool forward) {
    // run the action forward
    if (forward) {
        std::vector<QUuid> compileItems;
        action->forward(true, compileItems);
        applyCompile(std::move(compileItems));
    }

    // remove items ahead of where we are
    _stack.erase(_stack.begin() + _stackPos, _stack.end());

    // if the stack is going to be longer than max size, remove the first item
    if (_stack.size() == maxActions) {
        _stack.erase(_stack.begin());
    } else
        _stackPos++;

    _stack.push_back(std::move(action));

    stackChanged();
}

bool HistoryList::canUndo() const {
    return _stackPos > 0;
}

Action::ActionType HistoryList::undoType() const {
    if (canUndo()) return _stack[_stackPos - 1]->actionType();
    return Action::ActionType::NONE;
}

void HistoryList::undo() {
    if (!canUndo()) return;

    _stackPos--;
    auto undoAction = _stack[_stackPos].get();
    std::vector<QUuid> compileItems;
    undoAction->backward(compileItems);
    applyCompile(std::move(compileItems));

    stackChanged();
}

bool HistoryList::canRedo() const {
    return _stackPos < _stack.size();
}

Action::ActionType HistoryList::redoType() const {
    if (canRedo()) return _stack[_stackPos]->actionType();
    return Action::ActionType::NONE;
}

void HistoryList::redo() {
    if (!canRedo()) return;

    auto redoAction = _stack[_stackPos].get();
    std::vector<QUuid> compileItems;
    redoAction->forward(false, compileItems);
    _stackPos++;

    applyCompile(std::move(compileItems));

    stackChanged();
}
