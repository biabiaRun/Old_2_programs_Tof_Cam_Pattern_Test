
############################################
#
# How to build libarchive
#
############################################

# Public headers
SET(include_HEADERS
  archive.h
  archive_entry.h
)

# Sources and private headers
SET(zipUtils_SOURCES
  archive_acl.c
  archive_check_magic.c
  archive_cmdline.c
  archive_cmdline_private.h
  archive_crc32.h
  archive_cryptor.c
  archive_cryptor_private.h
  archive_digest.c
  archive_digest_private.h
  archive_endian.h
  archive_entry.c
  archive_entry.h
  archive_entry_copy_stat.c
  archive_entry_link_resolver.c
  archive_entry_locale.h
  archive_entry_private.h
  archive_entry_sparse.c
  archive_entry_stat.c
  archive_entry_strmode.c
  archive_entry_xattr.c
  archive_getdate.c
  archive_hmac.c
  archive_hmac_private.h
  archive_match.c
  archive_options.c
  archive_options_private.h
  archive_pack_dev.h
  archive_pack_dev.c
  archive_pathmatch.c
  archive_pathmatch.h
  archive_platform.h
  archive_ppmd_private.h
  archive_ppmd7.c
  archive_ppmd7_private.h
  archive_private.h
  archive_random.c
  archive_random_private.h
  archive_rb.c
  archive_rb.h
  archive_read.c
  archive_read_add_passphrase.c
  archive_read_append_filter.c
  archive_read_data_into_fd.c
  archive_read_disk_entry_from_file.c
  archive_read_disk_posix.c
  archive_read_disk_private.h
  archive_read_disk_set_standard_lookup.c
  archive_read_extract.c
  archive_read_extract2.c
  archive_read_open_fd.c
  archive_read_open_file.c
  archive_read_open_filename.c
  archive_read_open_memory.c
  archive_read_private.h
  archive_read_set_format.c
  archive_read_set_options.c
  archive_read_support_filter_all.c
  archive_read_support_filter_bzip2.c
  archive_read_support_filter_compress.c
  archive_read_support_filter_gzip.c
  archive_read_support_filter_grzip.c
  archive_read_support_filter_lrzip.c
  archive_read_support_filter_lz4.c
  archive_read_support_filter_lzop.c
  archive_read_support_filter_none.c
  archive_read_support_filter_program.c
  archive_read_support_filter_rpm.c
  archive_read_support_filter_uu.c
  archive_read_support_filter_xz.c
  archive_read_support_format_7zip.c
  archive_read_support_format_all.c
  archive_read_support_format_ar.c
  archive_read_support_format_by_code.c
  archive_read_support_format_cab.c
  archive_read_support_format_cpio.c
  archive_read_support_format_empty.c
  archive_read_support_format_iso9660.c
  archive_read_support_format_lha.c
  archive_read_support_format_mtree.c
  archive_read_support_format_rar.c
  archive_read_support_format_raw.c
  archive_read_support_format_tar.c
  archive_read_support_format_warc.c
  archive_read_support_format_xar.c
  archive_read_support_format_zip.c
  archive_string.c
  archive_string.h
  archive_string_composition.h
  archive_string_sprintf.c
  archive_util.c
  archive_virtual.c
  archive_write.c
  archive_write_disk_acl.c
  archive_write_disk_posix.c
  archive_write_disk_private.h
  archive_write_disk_set_standard_lookup.c
  archive_write_private.h
  archive_write_open_fd.c
  archive_write_open_file.c
  archive_write_open_filename.c
  archive_write_open_memory.c
  archive_write_add_filter.c
  archive_write_add_filter_b64encode.c
  archive_write_add_filter_by_name.c
  archive_write_add_filter_bzip2.c
  archive_write_add_filter_compress.c
  archive_write_add_filter_grzip.c
  archive_write_add_filter_gzip.c
  archive_write_add_filter_lrzip.c
  archive_write_add_filter_lz4.c
  archive_write_add_filter_lzop.c
  archive_write_add_filter_none.c
  archive_write_add_filter_program.c
  archive_write_add_filter_uuencode.c
  archive_write_add_filter_xz.c
  archive_write_set_format.c
  archive_write_set_format_7zip.c
  archive_write_set_format_ar.c
  archive_write_set_format_by_name.c
  archive_write_set_format_cpio.c
  archive_write_set_format_cpio_newc.c
  archive_write_set_format_filter_by_ext.c
  archive_write_set_format_gnutar.c
  archive_write_set_format_iso9660.c
  archive_write_set_format_mtree.c
  archive_write_set_format_pax.c
  archive_write_set_format_raw.c
  archive_write_set_format_shar.c
  archive_write_set_format_ustar.c
  archive_write_set_format_v7tar.c
  archive_write_set_format_warc.c
  archive_write_set_format_xar.c
  archive_write_set_format_zip.c
  archive_write_set_options.c
  archive_write_set_passphrase.c
  archive_xxhash.h
  filter_fork_posix.c
  filter_fork.h
  xxhash.c
)

# Man pages
SET(libarchive_MANS
  archive_entry.3
  archive_entry_acl.3
  archive_entry_linkify.3
  archive_entry_paths.3
  archive_entry_perms.3
  archive_entry_stat.3
  archive_entry_time.3
  archive_read.3
  archive_read_add_passphrase.3
  archive_read_disk.3
  archive_read_set_options.3
  archive_util.3
  archive_write.3
  archive_write_disk.3
  archive_write_set_options.3
  archive_write_set_passphrase.3
  cpio.5
  libarchive.3
  libarchive_internals.3
  libarchive-formats.5
  mtree.5
  tar.5
)

IF(WIN32 AND NOT CYGWIN)
  LIST(APPEND zipUtils_SOURCES archive_entry_copy_bhfi.c)
  LIST(APPEND zipUtils_SOURCES archive_read_disk_windows.c)
  LIST(APPEND zipUtils_SOURCES archive_windows.c)
  LIST(APPEND zipUtils_SOURCES archive_windows.h)
  LIST(APPEND zipUtils_SOURCES archive_write_disk_windows.c)
  LIST(APPEND zipUtils_SOURCES filter_fork_windows.c)
ENDIF(WIN32 AND NOT CYGWIN)

INCLUDE_DIRECTORIES(
	${ROYALE_ZLIB_INCLUDE_DIR}
	${ROYALE_ZLIB_BUILD_DIR}
	${ROYALE_BZLIB_INCLUDE_DIR}
	${ROYALE_LZMA_INCLUDE_DIR}/common
	${ROYALE_LZMA_INCLUDE_DIR}/lz
	${ROYALE_LZMA_INCLUDE_DIR}/lzma
	${ROYALE_LZMA_INCLUDE_DIR}/rangecoder
	${ROYALE_LZMA_INCLUDE_DIR}/simple
	${ROYALE_LZMA_INCLUDE_DIR}/subblock
)

# Libarchive is a shared library
ADD_LIBRARY(zipUtils SHARED ${zipUtils_SOURCES} ${include_HEADERS})
SET_TARGET_PROPERTIES(zipUtils PROPERTIES OUTPUT_NAME zipUtils FOLDER contrib/zip)
TARGET_COMPILE_DEFINITIONS(zipUtils PRIVATE _CRT_SECURE_NO_DEPRECATE archive_EXPORTS)
TARGET_LINK_LIBRARIES(zipUtils z libbz2static)

#ENDIF(NOT WIN32 OR CYGWIN)

# zipUtils_static is a static library
#ADD_LIBRARY(zipUtilsstatic STATIC ${zipUtils_SOURCES} ${include_HEADERS})
#TARGET_LINK_LIBRARIES(zipUtilsstatic zlibstatic libbz2static libLMZAstatic)
#SET_TARGET_PROPERTIES(zipUtilsstatic PROPERTIES COMPILE_DEFINITIONS LIBARCHIVE_STATIC OUTPUT_NAME zipUtilsstatic FOLDER contrib/zip)
# On Posix systems, libarchive.so and libarchive.a can co-exist.
