cmake_minimum_required(VERSION 2.6.)

get_filename_component(CIPHERTEXT bin/ciphertext.txt ABSOLUTE)
get_filename_component(RUS bin/rus.txt ABSOLUTE)

add_definitions (
    -DPRIMARY_DECODER_DEBUG
    -DCIPHER=${CIPHERTEXT}
    -DVOCABULARY=${RUS}
)

include_directories(dec_lib)
include_directories(primary_decoder)

add_subdirectory(dec_lib)
add_subdirectory(primary_decoder)
