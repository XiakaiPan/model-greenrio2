SUBDIRS = examples/elfdump examples/tutorial examples/writer examples/write_obj \
          examples/anonymizer examples/add_section

nobase_include_HEADERS = elfio/elf_types.hpp     elfio/elfio_dynamic.hpp    \
                         elfio/elfio.hpp         elfio/elfio_header.hpp     \
                         elfio/elfio_note.hpp    elfio/elfio_relocation.hpp \
                         elfio/elfio_section.hpp elfio/elfio_segment.hpp    \
                         elfio/elfio_strings.hpp elfio/elfio_symbols.hpp    \
                         elfio/elfio_utils.hpp   elfio/elfio_dump.hpp       \
                         elfio/elfio_version.hpp elfio/elfio_modinfo.hpp    \
                         elfio/elfio_array.hpp   elfio/elfio_versym.hpp

EXTRA_DIST = doc/elfio.pdf CMakeLists.txt examples/CMakeLists.txt cmake/elfioConfig.cmake.in

TESTS          = examples/elfdump/elfdump
LOG_COMPILER   = examples/elfdump/elfdump
