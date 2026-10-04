
#include <jni.h>
#include <link.h>
#include <android/log.h>
#include <filesystem>
#include <dlfcn.h>
#include<stdio.h>
#include<string.h>


#include "il2cpp/abi.h"
#include "sdk/mod.h"

#define SDK_VERSION 100
#define ZTAG "Znml"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, ZTAG, __VA_ARGS__)

#define LOAD_IL2CPP_API(name) \
    api_table->name = reinterpret_cast<decltype(api_table->name)>( \
        get_api_by_symbol(lib, #name)); \
    if(api_table->name == nullptr) cnt++;

il2cpp_funcs_t il2cpp_abi{};
static void* il2cpp_library_handle = nullptr;

struct mod_handle {
    void* handle;
    znml_mod_metadata_t* metadata;
};
std::vector<mod_handle> mod_handles;


void* get_api_by_symbol(void* lib_ptr, const char* symbol_name) {
    if(!lib_ptr || !symbol_name) {
        LOG("link: Invalid library pointer or symbol name");
        return nullptr;
    }
    void* ptr_ptr = dlsym(lib_ptr, symbol_name);
    LOG("link: %s -> %p",symbol_name, ptr_ptr);
    return ptr_ptr;
}

void* build_il2cpp_api_function_table(il2cpp_funcs_t* api_table) {

    if (!api_table) {
        return nullptr;
    }

    LOG("API table: opening libil2cpp.so");
    if (il2cpp_library_handle == nullptr) {
        il2cpp_library_handle = dlopen("libil2cpp.so", RTLD_NOW);
    }
    if(!il2cpp_library_handle){
        LOG("Failed to open libil2cpp.so: %s", dlerror());
        return nullptr;
    }
    void* lib = il2cpp_library_handle;
    int cnt = 0;
#if defined(IL2CPP_API_DYNAMIC_NO_DLSYM) && IL2CPP_API_DYNAMIC_NO_DLSYM
    LOAD_IL2CPP_API(il2cpp_api_register_symbols);
    LOAD_IL2CPP_API(il2cpp_api_lookup_symbol);
#endif
    LOAD_IL2CPP_API(il2cpp_init);
    LOAD_IL2CPP_API(il2cpp_init_utf16);
    LOAD_IL2CPP_API(il2cpp_shutdown);
    LOAD_IL2CPP_API(il2cpp_set_config_dir);
    LOAD_IL2CPP_API(il2cpp_set_data_dir);
    LOAD_IL2CPP_API(il2cpp_set_temp_dir);
    LOAD_IL2CPP_API(il2cpp_set_commandline_arguments);
    LOAD_IL2CPP_API(il2cpp_set_commandline_arguments_utf16);
    LOAD_IL2CPP_API(il2cpp_set_config_utf16);
    LOAD_IL2CPP_API(il2cpp_set_config);
    LOAD_IL2CPP_API(il2cpp_set_memory_callbacks);
    LOAD_IL2CPP_API(il2cpp_get_corlib);
    LOAD_IL2CPP_API(il2cpp_add_internal_call);
    LOAD_IL2CPP_API(il2cpp_resolve_icall);
    LOAD_IL2CPP_API(il2cpp_alloc);
    LOAD_IL2CPP_API(il2cpp_free);
    LOAD_IL2CPP_API(il2cpp_array_class_get);
    LOAD_IL2CPP_API(il2cpp_array_length);
    LOAD_IL2CPP_API(il2cpp_array_get_byte_length);
    LOAD_IL2CPP_API(il2cpp_array_new);
    LOAD_IL2CPP_API(il2cpp_array_new_specific);
    LOAD_IL2CPP_API(il2cpp_array_new_full);
    LOAD_IL2CPP_API(il2cpp_bounded_array_class_get);
    LOAD_IL2CPP_API(il2cpp_array_element_size);
    LOAD_IL2CPP_API(il2cpp_assembly_get_image);
    LOAD_IL2CPP_API(il2cpp_class_for_each);
    LOAD_IL2CPP_API(il2cpp_class_enum_basetype);
    LOAD_IL2CPP_API(il2cpp_class_is_generic);
    LOAD_IL2CPP_API(il2cpp_class_is_inflated);
    LOAD_IL2CPP_API(il2cpp_class_is_assignable_from);
    LOAD_IL2CPP_API(il2cpp_class_is_subclass_of);
    LOAD_IL2CPP_API(il2cpp_class_has_parent);
    LOAD_IL2CPP_API(il2cpp_class_from_il2cpp_type);
    LOAD_IL2CPP_API(il2cpp_class_from_name);
    LOAD_IL2CPP_API(il2cpp_class_from_system_type);
    LOAD_IL2CPP_API(il2cpp_class_get_element_class);
    LOAD_IL2CPP_API(il2cpp_class_get_events);
    LOAD_IL2CPP_API(il2cpp_class_get_fields);
    LOAD_IL2CPP_API(il2cpp_class_get_nested_types);
    LOAD_IL2CPP_API(il2cpp_class_get_interfaces);
    LOAD_IL2CPP_API(il2cpp_class_get_properties);
    LOAD_IL2CPP_API(il2cpp_class_get_property_from_name);
    LOAD_IL2CPP_API(il2cpp_class_get_field_from_name);
    LOAD_IL2CPP_API(il2cpp_class_get_methods);
    LOAD_IL2CPP_API(il2cpp_class_get_method_from_name);
    LOAD_IL2CPP_API(il2cpp_class_get_name);
    LOAD_IL2CPP_API(il2cpp_type_get_name_chunked);
    LOAD_IL2CPP_API(il2cpp_class_get_namespace);
    LOAD_IL2CPP_API(il2cpp_class_get_parent);
    LOAD_IL2CPP_API(il2cpp_class_get_declaring_type);
    LOAD_IL2CPP_API(il2cpp_class_instance_size);
    LOAD_IL2CPP_API(il2cpp_class_num_fields);
    LOAD_IL2CPP_API(il2cpp_class_is_valuetype);
    LOAD_IL2CPP_API(il2cpp_class_value_size);
    LOAD_IL2CPP_API(il2cpp_class_is_blittable);
    LOAD_IL2CPP_API(il2cpp_class_get_flags);
    LOAD_IL2CPP_API(il2cpp_class_is_abstract);
    LOAD_IL2CPP_API(il2cpp_class_is_interface);
    LOAD_IL2CPP_API(il2cpp_class_array_element_size);
    LOAD_IL2CPP_API(il2cpp_class_from_type);
    LOAD_IL2CPP_API(il2cpp_class_get_type);
    LOAD_IL2CPP_API(il2cpp_class_get_type_token);
    LOAD_IL2CPP_API(il2cpp_class_has_attribute);
    LOAD_IL2CPP_API(il2cpp_class_has_references);
    LOAD_IL2CPP_API(il2cpp_class_is_enum);
    LOAD_IL2CPP_API(il2cpp_class_get_image);
    LOAD_IL2CPP_API(il2cpp_class_get_assemblyname);
    LOAD_IL2CPP_API(il2cpp_class_get_rank);
    LOAD_IL2CPP_API(il2cpp_class_get_data_size);
    LOAD_IL2CPP_API(il2cpp_class_get_static_field_data);
    LOAD_IL2CPP_API(il2cpp_class_get_bitmap_size);
    LOAD_IL2CPP_API(il2cpp_class_get_bitmap);
    LOAD_IL2CPP_API(il2cpp_stats_dump_to_file);
    LOAD_IL2CPP_API(il2cpp_stats_get_value);
    LOAD_IL2CPP_API(il2cpp_domain_get);
    LOAD_IL2CPP_API(il2cpp_domain_assembly_open);
    LOAD_IL2CPP_API(il2cpp_domain_get_assemblies);
    LOAD_IL2CPP_API(il2cpp_raise_exception);
    LOAD_IL2CPP_API(il2cpp_exception_from_name_msg);
    LOAD_IL2CPP_API(il2cpp_get_exception_argument_null);
    LOAD_IL2CPP_API(il2cpp_format_exception);
    LOAD_IL2CPP_API(il2cpp_format_stack_trace);
    LOAD_IL2CPP_API(il2cpp_unhandled_exception);
    LOAD_IL2CPP_API(il2cpp_native_stack_trace);
    LOAD_IL2CPP_API(il2cpp_field_get_flags);
    LOAD_IL2CPP_API(il2cpp_field_get_name);
    LOAD_IL2CPP_API(il2cpp_field_get_parent);
    LOAD_IL2CPP_API(il2cpp_field_get_offset);
    LOAD_IL2CPP_API(il2cpp_field_get_type);
    LOAD_IL2CPP_API(il2cpp_field_get_value);
    LOAD_IL2CPP_API(il2cpp_field_get_value_object);
    LOAD_IL2CPP_API(il2cpp_field_has_attribute);
    LOAD_IL2CPP_API(il2cpp_field_set_value);
    LOAD_IL2CPP_API(il2cpp_field_static_get_value);
    LOAD_IL2CPP_API(il2cpp_field_static_set_value);
    LOAD_IL2CPP_API(il2cpp_field_set_value_object);
    LOAD_IL2CPP_API(il2cpp_field_is_literal);
    LOAD_IL2CPP_API(il2cpp_gc_collect);
    LOAD_IL2CPP_API(il2cpp_gc_collect_a_little);
    LOAD_IL2CPP_API(il2cpp_gc_start_incremental_collection);
    LOAD_IL2CPP_API(il2cpp_gc_disable);
    LOAD_IL2CPP_API(il2cpp_gc_enable);
    LOAD_IL2CPP_API(il2cpp_gc_is_disabled);
    LOAD_IL2CPP_API(il2cpp_gc_set_mode);
    LOAD_IL2CPP_API(il2cpp_gc_get_max_time_slice_ns);
    LOAD_IL2CPP_API(il2cpp_gc_set_max_time_slice_ns);
    LOAD_IL2CPP_API(il2cpp_gc_is_incremental);
    LOAD_IL2CPP_API(il2cpp_gc_get_used_size);
    LOAD_IL2CPP_API(il2cpp_gc_get_heap_size);
    LOAD_IL2CPP_API(il2cpp_gc_wbarrier_set_field);
    LOAD_IL2CPP_API(il2cpp_gc_has_strict_wbarriers);
    LOAD_IL2CPP_API(il2cpp_gc_set_external_allocation_tracker);
    LOAD_IL2CPP_API(il2cpp_gc_set_external_wbarrier_tracker);
    LOAD_IL2CPP_API(il2cpp_gc_foreach_heap);
    LOAD_IL2CPP_API(il2cpp_stop_gc_world);
    LOAD_IL2CPP_API(il2cpp_start_gc_world);
    LOAD_IL2CPP_API(il2cpp_gchandle_new);
    LOAD_IL2CPP_API(il2cpp_gchandle_new_weakref);
    LOAD_IL2CPP_API(il2cpp_gchandle_get_target);
    LOAD_IL2CPP_API(il2cpp_gchandle_free);
    LOAD_IL2CPP_API(il2cpp_gchandle_foreach_get_target);
    LOAD_IL2CPP_API(il2cpp_object_header_size);
    LOAD_IL2CPP_API(il2cpp_array_object_header_size);
    LOAD_IL2CPP_API(il2cpp_offset_of_array_length_in_array_object_header);
    LOAD_IL2CPP_API(il2cpp_offset_of_array_bounds_in_array_object_header);
    LOAD_IL2CPP_API(il2cpp_allocation_granularity);
    LOAD_IL2CPP_API(il2cpp_unity_liveness_calculation_begin);
    LOAD_IL2CPP_API(il2cpp_unity_liveness_calculation_end);
    LOAD_IL2CPP_API(il2cpp_unity_liveness_calculation_from_root);
    LOAD_IL2CPP_API(il2cpp_unity_liveness_calculation_from_statics);
    LOAD_IL2CPP_API(il2cpp_method_get_return_type);
    LOAD_IL2CPP_API(il2cpp_method_get_declaring_type);
    LOAD_IL2CPP_API(il2cpp_method_get_name);
    LOAD_IL2CPP_API(il2cpp_method_get_from_reflection);
    LOAD_IL2CPP_API(il2cpp_method_get_object);
    LOAD_IL2CPP_API(il2cpp_method_is_generic);
    LOAD_IL2CPP_API(il2cpp_method_is_inflated);
    LOAD_IL2CPP_API(il2cpp_method_is_instance);
    LOAD_IL2CPP_API(il2cpp_method_get_param_count);
    LOAD_IL2CPP_API(il2cpp_method_get_param);
    LOAD_IL2CPP_API(il2cpp_method_get_class);
    LOAD_IL2CPP_API(il2cpp_method_has_attribute);
    LOAD_IL2CPP_API(il2cpp_method_get_flags);
    LOAD_IL2CPP_API(il2cpp_method_get_token);
    LOAD_IL2CPP_API(il2cpp_method_get_param_name);
    LOAD_IL2CPP_API(il2cpp_profiler_install);
    LOAD_IL2CPP_API(il2cpp_profiler_set_events);
    LOAD_IL2CPP_API(il2cpp_profiler_install_enter_leave);
    LOAD_IL2CPP_API(il2cpp_profiler_install_allocation);
    LOAD_IL2CPP_API(il2cpp_profiler_install_gc);
    LOAD_IL2CPP_API(il2cpp_profiler_install_fileio);
    LOAD_IL2CPP_API(il2cpp_profiler_install_thread);
    LOAD_IL2CPP_API(il2cpp_property_get_flags);
    LOAD_IL2CPP_API(il2cpp_property_get_get_method);
    LOAD_IL2CPP_API(il2cpp_property_get_set_method);
    LOAD_IL2CPP_API(il2cpp_property_get_name);
    LOAD_IL2CPP_API(il2cpp_property_get_parent);
    LOAD_IL2CPP_API(il2cpp_object_get_class);
    LOAD_IL2CPP_API(il2cpp_object_get_size);
    LOAD_IL2CPP_API(il2cpp_object_get_virtual_method);
    LOAD_IL2CPP_API(il2cpp_object_new);
    LOAD_IL2CPP_API(il2cpp_object_unbox);
    LOAD_IL2CPP_API(il2cpp_value_box);
    LOAD_IL2CPP_API(il2cpp_monitor_enter);
    LOAD_IL2CPP_API(il2cpp_monitor_try_enter);
    LOAD_IL2CPP_API(il2cpp_monitor_exit);
    LOAD_IL2CPP_API(il2cpp_monitor_pulse);
    LOAD_IL2CPP_API(il2cpp_monitor_pulse_all);
    LOAD_IL2CPP_API(il2cpp_monitor_wait);
    LOAD_IL2CPP_API(il2cpp_monitor_try_wait);
    LOAD_IL2CPP_API(il2cpp_runtime_invoke);
    LOAD_IL2CPP_API(il2cpp_runtime_invoke_convert_args);
    LOAD_IL2CPP_API(il2cpp_runtime_class_init);
    LOAD_IL2CPP_API(il2cpp_runtime_object_init);
    LOAD_IL2CPP_API(il2cpp_runtime_object_init_exception);
    LOAD_IL2CPP_API(il2cpp_runtime_unhandled_exception_policy_set);
    LOAD_IL2CPP_API(il2cpp_string_length);
    LOAD_IL2CPP_API(il2cpp_string_chars);
    LOAD_IL2CPP_API(il2cpp_string_new);
    LOAD_IL2CPP_API(il2cpp_string_new_len);
    LOAD_IL2CPP_API(il2cpp_string_new_utf16);
    LOAD_IL2CPP_API(il2cpp_string_new_wrapper);
    LOAD_IL2CPP_API(il2cpp_string_intern);
    LOAD_IL2CPP_API(il2cpp_string_is_interned);
    LOAD_IL2CPP_API(il2cpp_thread_current);
    LOAD_IL2CPP_API(il2cpp_thread_attach);
    LOAD_IL2CPP_API(il2cpp_thread_detach);
    LOAD_IL2CPP_API(il2cpp_thread_get_all_attached_threads);
    LOAD_IL2CPP_API(il2cpp_is_vm_thread);
    LOAD_IL2CPP_API(il2cpp_current_thread_walk_frame_stack);
    LOAD_IL2CPP_API(il2cpp_thread_walk_frame_stack);
    LOAD_IL2CPP_API(il2cpp_current_thread_get_top_frame);
    LOAD_IL2CPP_API(il2cpp_thread_get_top_frame);
    LOAD_IL2CPP_API(il2cpp_current_thread_get_frame_at);
    LOAD_IL2CPP_API(il2cpp_thread_get_frame_at);
    LOAD_IL2CPP_API(il2cpp_current_thread_get_stack_depth);
    LOAD_IL2CPP_API(il2cpp_thread_get_stack_depth);
    LOAD_IL2CPP_API(il2cpp_override_stack_backtrace);
    LOAD_IL2CPP_API(il2cpp_type_get_object);
    LOAD_IL2CPP_API(il2cpp_type_get_type);
    LOAD_IL2CPP_API(il2cpp_type_get_class_or_element_class);
    LOAD_IL2CPP_API(il2cpp_type_get_name);
    LOAD_IL2CPP_API(il2cpp_type_is_byref);
    LOAD_IL2CPP_API(il2cpp_type_get_attrs);
    LOAD_IL2CPP_API(il2cpp_type_equals);
    LOAD_IL2CPP_API(il2cpp_type_get_assembly_qualified_name);
    LOAD_IL2CPP_API(il2cpp_type_is_static);
    LOAD_IL2CPP_API(il2cpp_type_is_pointer_type);
    LOAD_IL2CPP_API(il2cpp_image_get_assembly);
    LOAD_IL2CPP_API(il2cpp_image_get_name);
    LOAD_IL2CPP_API(il2cpp_image_get_filename);
    LOAD_IL2CPP_API(il2cpp_image_get_entry_point);
    LOAD_IL2CPP_API(il2cpp_image_get_class_count);
    LOAD_IL2CPP_API(il2cpp_image_get_class);
    LOAD_IL2CPP_API(il2cpp_capture_memory_snapshot);
    LOAD_IL2CPP_API(il2cpp_free_captured_memory_snapshot);
    LOAD_IL2CPP_API(il2cpp_set_find_plugin_callback);
    LOAD_IL2CPP_API(il2cpp_register_log_callback);
    LOAD_IL2CPP_API(il2cpp_debugger_set_agent_options);
    LOAD_IL2CPP_API(il2cpp_is_debugger_attached);
    LOAD_IL2CPP_API(il2cpp_register_debugger_agent_transport);
    LOAD_IL2CPP_API(il2cpp_debug_get_method_info);
    LOAD_IL2CPP_API(il2cpp_unity_install_unitytls_interface);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_from_class);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_from_method);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_get_attr);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_has_attr);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_construct);
    LOAD_IL2CPP_API(il2cpp_custom_attrs_free);
    LOAD_IL2CPP_API(il2cpp_class_set_userdata);
    LOAD_IL2CPP_API(il2cpp_class_get_userdata_offset);
    LOAD_IL2CPP_API(il2cpp_set_default_thread_affinity);
    LOG("API table: symbol scan finished, missing=%d", cnt);
    if(cnt > 233 / 2){
        LOG("Warning: %d symbols failed to load from libil2cpp.so", cnt);
    }
#undef LOAD_IL2CPP_API
    return api_table;
}

static void mods_on_load() {
    LOG("mods_on_load: registered mods=%zu", mod_handles.size());
    for(auto& mod : mod_handles) {
        if(mod.metadata && mod.metadata->on_load) {
            LOG("Calling on_load for mod: %s", mod.metadata->name);
            bool success = mod.metadata->on_load(&il2cpp_abi);
            if(!success) {
                LOG("Mod %s failed to load properly", mod.metadata->name);
            }
        }else
        {
            LOG("Warning: Mod %s has no on_load function,it may not work", mod.metadata ? mod.metadata->name : "Unknown");
        }
    }
}
static void load_mods(const std::filesystem::path& path){
    LOG("load_mods: scanning directory %s", path.c_str());
    if(!std::filesystem::exists(path)){
        LOG("Mods directory does not exist: %s", path.c_str());
        return;
    }
    size_t candidate_count = 0;
    for(const auto& entry : std::filesystem::directory_iterator(path)){
        if(entry.is_regular_file() && entry.path().extension() == ".so"){
            candidate_count++;
            LOG("Loading mod: %s", entry.path().c_str());
            void* handle = dlopen(entry.path().c_str(), RTLD_NOW);
            if(!handle){
                LOG("Failed to load mod, skipping: %s", dlerror());
            }else{
                znml_mod_metadata_t* mod_metadata = reinterpret_cast<znml_mod_metadata_t*>(dlsym(handle, MOD_SYMBOL));
                if(!mod_metadata){
                    LOG("Failed to find mod metadata, skipping: %s", dlerror());
                    dlclose(handle);
                    continue;
                }
                if(mod_metadata->target_sdk_ver < SDK_VERSION){
                    LOG("Unsupported SDK version , loader: %d mod: %s", SDK_VERSION, mod_metadata->name);
                    dlclose(handle);
                    continue;
                }
                const char* mod_id = mod_metadata->id , *mod_name = mod_metadata->name , *mod_version = mod_metadata->version , *mod_author = mod_metadata->author;
                if(mod_id && mod_name && mod_version && mod_author){
                    LOG("Loaded Mod: %s", entry.path().c_str());
                    LOG("- id: %s", mod_id);
                    LOG("- name: %s", mod_name);
                    LOG("- version: %s", mod_version);
                    LOG("- author: %s", mod_author);
                    mod_handles.push_back({handle, mod_metadata});
                }else{
                    LOG("Missing required fields in mod metadata, skipping: %s", entry.path().c_str());
                    dlclose(handle);
                    continue;
                }
            }
        }
    }
    LOG("load_mods: .so candidates=%zu accepted=%zu", candidate_count, mod_handles.size());
}

static jboolean Java_com_unity3d_player_NativeLoader_load(JNIEnv* env, jclass clazz, jstring path) {
    std::filesystem::path nativePath = env->GetStringUTFChars(path, nullptr);
    if(nativePath.empty()) {
        LOG(">>> NativeLoader.load called with empty path");
        return false;
    }
    if(!std::filesystem::exists(nativePath)) {
        LOG(">>> NativeLoader.load called with non-existent path: %s", nativePath.c_str());
        return false;
    }
    LOG(">>> NativeLoader.load called with path: %s", nativePath.c_str());  
    LOG(">>> Initializing...");
    LOG(" _____                   _ ");
    LOG("/ _  / _ __   _ __ ___  | |");
    LOG("\\// / | '_ \\ | '_ ` _ \\ | |");
    LOG(" / //\\| | | || | | | | || |");
    LOG("/____/|_| |_||_| |_| |_||_|");
    LOG("------- Z native mod loader");

    LOG(">>> Resolving IL2CPP API table...");
    if (build_il2cpp_api_function_table(&il2cpp_abi) == nullptr) {
        LOG("Failed to build Il2CppApiFunctionTable");
        return false;
    }
    LOG(">>> Il2CppApiFunctionTable built successfully");

    std::filesystem::path modsPath = nativePath / "mods";
    if(!std::filesystem::exists(modsPath)) std::filesystem::create_directories(modsPath);
    LOG(">>> Loading mods from path: %s", modsPath.c_str());
    load_mods(modsPath);
    mods_on_load();
    LOG(">>> Mods loaded successfully");
    return true;
}

extern "C" 
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOG(">>> Dynamic library loaded");
    JNIEnv* env;
    vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    jclass clazz = env->FindClass("com/unity3d/player/NativeLoader");
    JNINativeMethod method[] = {{"load", "(Ljava/lang/String;)Z", (void*)Java_com_unity3d_player_NativeLoader_load}};
    env->RegisterNatives(clazz, method, 1);
    return JNI_VERSION_1_6;
}

