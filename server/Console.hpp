#pragma once


#include <Nuts/EcsCore/Event.hpp>
#include <Utilities.hpp>
#include <unordered_map>

/**
 * @brief Static singleton class, not meant to be instantiated
 * usage: Console::
 */
class Console
{
    inline static void cmd_quit()
    {
        // MUGUARD(gRunning_mutex);
        *_running = false;
    }

    inline static void cmd_exit()
    {
        COUT("did you mean \"quit\" ?\n");
    }

    inline static void cmd_clear()
    {
        system("cls");
    }

    inline static void cmd_help()
    {
        COUT("Available commands:\n");
        for (auto &c : cmd_commands) {
            COUT(c.first << "\n");
        }
    }

    inline static void cmd_tab()
    {
        COUT("Nice try!\n");
    }

    inline static void cmd_games()
    {

    }

    using callback = std::function<void()>;
    inline static std::unordered_map<std::string, callback> cmd_commands {
        { "/quit", &cmd_quit },
        { "/exit", &cmd_exit },
        { "/cls", &cmd_clear },
        { "/clear", &cmd_clear },
        { "/games", &cmd_games },
        { "/help", &cmd_help },
    };

    Console() {};

    static inline bool *_running = nullptr;

public:
    static Console &single_instance()
    {
        static Console cmd;
        return cmd;
    }

    static void handleCmdlineInput(bool *running)
    {
        _running = running;

        std::string str;
        while (*running) {

            std::cin >> str;

            bool command_exists = (cmd_commands.find(str) != cmd_commands.end());

            if ((str.size() > 1) & command_exists) {
                cmd_commands[str]();

            } else if (!command_exists) {
                COUT("try \"/help\"\n");
            }
        }
    }
};