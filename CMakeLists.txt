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
        service/billing_service.c
        service/billing_service.h
        file/card_file.c
        file/card_file.h
        file/billing_file.c
        file/billing_file.h
        tool.c
        tool.h
        model.h
        enities/linked_list.h
        enities/linked_list.c
        global.h
        service/money_service.h
        service/money_service.c
        file/money_file.h
        file/money_file.c
)
