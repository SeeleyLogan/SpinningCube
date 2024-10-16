#include <SpinningCube.h>

#define LINUX_STRCPY(dest, pattern, dest_len, ...) 			\
	{ 														\
		dest = REALLOC(NULL, dest_len); 					\
		memcpy(dest, pattern, dest_len); 					\
		__VA_ARGS__ 										\
	}

#define LINUX_FILE_LOOP(regex, regex_prog, dir, ...) 			\
	{ 															\
		dir = opendir(path); 									\
		while ((dirent = readdir(dir))) 						\
		{ 														\
			const char* filename = dirent->d_name; 				\
			if (!regexec(&regex_prog, filename, 0, NULL, 0)) 	\
			{ 													\
				__VA_ARGS__ 									\
			} 													\
		} 														\
	}

#define WIN_FILE_LOOP(regex, ...) 								\
	{ 															\
		WIN32_FIND_DATAA file_data; 							\
		HANDLE file_handle = FindFirstFileA(regex, &file_data); \
		do 														\
		{ 														\
			char* file_name = file_data.cFileName; 				\
			__VA_ARGS__ 										\
		}														\
		while (FindNextFileA(file_handle, &file_data)); 		\
	}

Glob glob_files(const char* restrict pattern)
{
	u32 filename_strlen_sum = 0;
	char** file_array;
	char* file_name_array;
    u32 i = 0;

	#ifdef linux

	u32 path_len = strrchr(pattern, '/') - pattern + 1;
	u32 regex_len = strlen(pattern) - path_len + 1;
	char* path; char* regex;
	
	LINUX_STRCPY(path, pattern, path_len, path[path_len] = 0;)
	LINUX_STRCPY(regex, pattern + path_len, regex_len)

	regex_t regex_prog;
	if (regcomp(&regex_prog, regex, REG_ICASE | REG_NOSUB))
		ERROR(1, "error: an issued occurred during glob\n")

	struct dirent* dirent;

	DIR* dir;		
	LINUX_FILE_LOOP
	(
		regex, regex_prog, dir,
		i++;
		filename_strlen_sum += strlen(filename);
	)

	file_array = REALLOC(NULL, sizeof(char*) * i);
	file_name_array = REALLOC(NULL, filename_strlen_sum + i);

	if (regcomp(&regex_prog, regex, REG_ICASE | REG_NOSUB))
		ERROR(1, "error: an issued occurred during glob\n")

	i = 0;
	filename_strlen_sum = 0;
	dir = opendir(path);
	LINUX_FILE_LOOP
	(
		regex, regex_prog, dir,
		u32 file_name_strlen = strlen(filename)+1;
		memcpy(file_name_array + filename_strlen_sum, filename, file_name_strlen);
		file_array[i] = file_name_array + filename_strlen_sum;
		filename_strlen_sum += file_name_strlen;
		i++;
	)

	FREE(path);
	FREE(regex);
	regfree(&regex_prog);

	#else

	//WIN_FILE_LOOP
	(
		pattern,
		i++;
		filename_strlen_sum += strlen(file_name);
	)
	
	file_array = REALLOC(NULL, sizeof(char*) * i);
	file_name_array = REALLOC(NULL, filename_strlen_sum + i);
	
	i = 0;
	filename_strlen_sum = 0;
	WIN_FILE_LOOP
	(
		pattern,
		MGFW_u32 file_name_strlen = strlen(file_name)+1;
		memcpy(file_name_array + filename_strlen_sum, file_name, file_name_strlen);
		file_array[i] = file_name_array + filename_strlen_sum;
		filename_strlen_sum += file_name_strlen;
		i++;
	)

    #endif

	Glob glob_result =
	{
		file_array,
		i
	};

    return glob_result;
}

inline void free_glob(Glob* glob)
{
	FREE(glob->file_array);
}

