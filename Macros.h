
#pragma once

#define CLOSE_RETURN_NULL(fp) {fclose(fp);return NULL;}
#define CLOSE_FILE_IF_NULL(ptr,fp) {if(!ptr) CLOSE_RETURN_NULL(fp)}
#define CLOSE_FILE_AND_FREE(ptr,fp) {free(ptr); CLOSE_RETURN_NULL(fp)}
