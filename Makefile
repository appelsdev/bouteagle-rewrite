COMPILER = C:/Apps/Tools/LLVM/bin/clang++.exe
LINKER   = C:/Apps/Tools/LLVM/bin/clang++.exe
CFLAGS   = -pipe -Xclang -flto-visibility-public-std -Wall -Werror -Wno-missing-braces -Wno-unsequenced -Wno-c++11-narrowing
LFLAGS   = -lopengl32 -lgdi32 -luser32 -lglew32 -lcal3d -lfreetype -lws2_32 -llibxml2 -lAceGames -Wl,-machine:x86
TARGET   = BoutEagle.exe
SRCEXT   = .cpp
LIBDIRS  = -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17763.0\um\x86" -L"C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/lib" -L"./external/lib"
INCDIRS  = -I ./external/include/ -I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\um" -I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\shared"

# Define basic commands.
kill     = taskkill /f /im $(1)>nul 2>&1||(exit 0)
#move     = move /y $(1) $(addprefix external/lib/,$(1))

# Define a recursive wildcard function.
# Usage: $(call rwildcard, <directory>, <file pattern>)
define rwildcard
	$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))
endef

# Gather list of source files.
srcfiles := $(call rwildcard, src/, %$(SRCEXT))
srcfiles_acegames := $(call rwildcard, acegames/, %.cpp)

# Create list of object files from source files,
# every file in the list that does not exist yet
# will be compiled automatically.
objects  := $(patsubst %$(SRCEXT), %.o, $(srcfiles))
objects  := $(objects:src/%=obj/%)
objects_acegames  := $(patsubst %.cpp, %.o, $(srcfiles_acegames))
objects_acegames  := $(objects_acegames:acegames/%=obj/acegames/%)



# Debug target.
all: debug
debug: CFLAGS += -O0 -fno-omit-frame-pointer -DDEBUG -Wno-unused -ggdb
debug: LFLAGS += -Wl,/SUBSYSTEM:CONSOLE -ggdb
debug: $(objects)
	$(LINKER) -o $(TARGET) $^ $(LFLAGS) $(LIBDIRS)

# Release target.
release: CFLAGS += -O3
release: LFLAGS += -Wl,/SUBSYSTEM:WINDOWS
release: $(objects)
	$(LINKER) -o $(TARGET) $^ $(LFLAGS) $(LIBDIRS)


# AceGames DLL target.
acegames: $(objects_acegames)
	$(LINKER) -shared -o AceGames.dll $^ -luser32 -lws2_32 $(LIBDIRS)


# Target for every required object in the specified target.
$(objects): obj/%.o: src/%$(SRCEXT)
	@mkdir -p $(dir $@)
	$(COMPILER) -I ./include/ $(INCDIRS) $(CFLAGS) -c $^ -o $@

$(objects_acegames): obj/acegames/%.o: acegames/%.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) -I ./acegames/ $(INCDIRS) $(CFLAGS) -DACEGAMES_DLL -c $^ -o $@


# 'make clean' removes the specified target file
# and the specified object directory.
.PHONY: clean
clean:
	@rm -f $(TARGET)
	@rm -rf obj/
clean_acegames :
	@rm -f AceGames.dll
	@rm -rf obj/acegames/
