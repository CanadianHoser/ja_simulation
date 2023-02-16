# https://r4nd0m6uy.ch/cmake-and-cpputest.html

# (1) Build a library with my application sources
set(APP_LIB_SOURCE
    aircraft.cpp
)

add_library(${APP_LIB_NAME} ${APP_LIB_SOURCE})

# (2) Add main(..) to the application library to have something we can run
add_executable(${APP_NAME} simulation_main.cpp)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME})
