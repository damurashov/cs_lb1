project(primary_decoder)
add_executable(decode 
    main.cpp 
    print_ops.cpp
    arg_handler.cpp
)
target_link_libraries(decode dec_lib)
