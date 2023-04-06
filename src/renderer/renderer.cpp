#include "plugins/plugin.h"
#include "plugins/plugin_loader.h"
#include "plugins/plugin_procedure_names.h"

#include <nox/renderer/renderer.h>

namespace NOX {

std::unique_ptr<Renderer, RendererDeleter> Renderer::create(std::string_view rendererName) {
    NOX_DECLARE_PLUGIN_FUNCTION(AllocateRendererFunction, void *, void);
    NOX_DECLARE_PLUGIN_FUNCTION(DeallocateRendererFunction, void, void *);

    const auto *plugin = PluginLoader::instance().loadPlugin(rendererName);
    auto *allocateProcedure = plugin->loadProcedure(RendererPlugin::allocateRendererProcedureName);
    auto *allocateRendererFunction = reinterpret_cast<AllocateRendererFunction>(allocateProcedure);
    auto *deallocateProcedure = plugin->loadProcedure(RendererPlugin::deallocateRendererProcedureName);
    auto *deallocateRendererFunction = reinterpret_cast<DeallocateRendererFunction>(deallocateProcedure);

    auto *renderer = reinterpret_cast<Renderer *>(allocateRendererFunction());
    auto deleter = [deallocateRendererFunction, plugin](Renderer *renderer) {
        deallocateRendererFunction(renderer);
        PluginLoader::instance().unloadPlugin(plugin);
    };

    return {renderer, deleter};
}

} // namespace NOX