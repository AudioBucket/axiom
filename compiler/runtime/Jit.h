#pragma once

#include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
#include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
#include <llvm/ExecutionEngine/Orc/IRTransformLayer.h>
#include <llvm/IR/Mangler.h>

#include <unordered_map>

namespace llvm {
    class Module;
}

namespace MaximRuntime {

    class Jit {
    private:
        using ObjectLayer = llvm::orc::RTDyldObjectLinkingLayer;
        using CompileLayer = llvm::orc::IRCompileLayer<ObjectLayer, llvm::orc::SimpleCompiler>;
        using OptimizeFunction = std::function<std::shared_ptr<llvm::Module>(std::shared_ptr<llvm::Module>)>;
        using OptimizeLayer = llvm::orc::IRTransformLayer<CompileLayer, OptimizeFunction>;

    public:
        using ModuleKey = CompileLayer::ModuleHandleT;

        Jit();

        llvm::DataLayout const &dataLayout() const { return _dataLayout; }

        ModuleKey addModule(std::unique_ptr<llvm::Module> m);

        ModuleKey addModule(const llvm::Module &m);

        void removeModule(ModuleKey k);

        llvm::JITSymbol findSymbol(const std::string &name);

        llvm::JITSymbol findSymbol(llvm::GlobalValue *value);

        llvm::JITTargetAddress getSymbolAddress(const std::string &name);

        llvm::JITTargetAddress getSymbolAddress(llvm::GlobalValue *value);

        std::shared_ptr<llvm::Module> optimizeModule(std::shared_ptr<llvm::Module> m);

    private:
        llvm::TargetMachine *targetMachine;
        const llvm::DataLayout _dataLayout;
        ObjectLayer objectLayer;
        CompileLayer compileLayer;
        OptimizeLayer optimizeLayer;
        llvm::Mangler mangler;
    };

}
