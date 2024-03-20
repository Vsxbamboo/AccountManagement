cmake_minimum_required(VERSION 3.26)
project(AccountManagement C)

set(CMAKE_C_STANDARD 11)
add_executable(AccountManagement main.c
        menu.h
        menu.c
        service/service.c
        service/service.h
        service/card_service.c
        service/card_service.h
        service/rate_service.c
        service/rate_service.h
        service/billing_service.c
        service/billing_service.h
        service/record_service.c
        service/record_service.h
        file/rate_file.c
        file/rate_file.h
        file/card_file.c
        file/card_file.h
        file/billing_file.c
        file/billing_file.h
        file/record_file.c
        file/record_file.h
        tool.c
        tool.h
        model.h
        global.c
        global.c
        demo/LinkedListDemo.c
        demo/LinkedListDemo.h
)
