#pragma once

#define EDGE_CHECK_CALL(check_val, function) if (!(check_val)) { function; }
#define EDGE_CHECK_INITIALIZATION(check_val) if (!(check_val)) { release(); return false; }
#define EDGE_CHECK_RETURN_FALSE(check_val) if (!(check_val)) { return false; }
#define EDGE_CHECK_RETURN_NULL(check_val) if (!(check_val)) { return nullptr; }

#define EDGE_ALLOCATE_RAW(type, size) ( reinterpret_cast<type*>(new uint8_t[size]))

#define EDGE_SAFE_DEALLOCATE_RAW(obj, type) { if (obj) { obj->~type(); uint8_t* rawPtr = reinterpret_cast<uint8_t*>(obj); delete[] rawPtr; obj = nullptr; }}
#define EDGE_SAFE_DEALLOCATE_RAW_WITHOUT_DSTR(obj) { if (obj) { uint8_t* rawPtr = reinterpret_cast<uint8_t*>(obj); delete[] rawPtr; obj = nullptr; }}

#define EDGE_SAFE_DESTROY(obj) { if (obj) { delete obj; obj = nullptr; }}
#define EDGE_SAFE_DESTROY_ARRAY(obj) { if (obj) { delete[] obj; obj = nullptr; }}
#define EDGE_SAFE_DESTROY_WITH_RELEASING(obj) { if (obj) { obj->release(); delete obj; obj = nullptr; }}

#define EDGE_SAFE_CALL(ft) { if(ft) { ft(); } }
#define EDGE_SAFE_CALL_ARGS(ft, ...) { if(ft) { ft(__VA_ARGS__); } }