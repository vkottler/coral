/**
 * \file
 * \brief A command-line argument application interface.
 */
#pragma once

/* internal */
#include "CommandLine.h"
#include "StringCommandProcessor.h"

namespace Coral
{

static constexpr std::size_t default_max_line = 256;

static constexpr std::size_t default_max_commands = 16;

template <std::size_t max_commands = default_max_commands,
          std::size_t depth = default_max_line,
          std::size_t max_args = default_max_args, typename element_t = char,
          class T = PrintfLogger>
class ElementCommandLineApp : public HasLogInterface<T>
{
  public:
    using CommandLine = ElementCommandLine<element_t, T>;
    using Processor = StringCommandProcessor<depth, element_t, max_args>;

    using Handler = std::function<void(CommandLine &)>;

    using CommandRegistration = std::function<void(ElementCommandLineApp &)>;

    ElementCommandLineApp(CommandRegistration register_commands,
                          typename Processor::Buffer &input,
                          LogInterface<T> *_log = nullptr)
        : HasLogInterface<T>(_log),
          processor(/* LCOV_EXCL_LINE */
                    input,
                    [this](const element_t **argv, std::size_t argc) {
                        process(argv, argc);
                    },
                    true /* auto_poll */),
          commands(), command_index(0)
    {
        add_handler("help", [this](CommandLine &cli) { help(cli); });
        register_commands(*this);
    }

    /* interface for registering a command */
    void add_handler(const element_t *command, Handler handler,
                     const char *help = nullptr,
                     LogInterface<T> *_log = nullptr)
    {
        this->log(_log, "Added command handler for '%s'.\n", command);

        commands[command_index].command = command;
        commands[command_index].handler = handler;
        commands[command_index].help = help;
        command_index++;
    }

    void process(const element_t **argv, std::size_t argc)
    {
        CommandLine cli(argv, argc, this->logger);

        bool handled = false;

        for (std::size_t i = 0; i < command_index; i++)
        {
            auto &cmd = commands[i];
            handled = cmd.handle(cli);
            if (handled)
            {
                break;
            }
        }

        if (not handled)
        {
            this->log(nullptr, "Command '%s' not found.\n",
                      cli.get_command().c_str());
            help(cli);
        }
    }

  protected:
    Processor processor;

    void help(CommandLine &cli)
    {
        (void)cli;

        this->log(nullptr, "%zu commands registered:\n", command_index);

        for (std::size_t i = 0; i < command_index; i++)
        {
            auto &cmd = commands[i];
            this->log(nullptr, "  %s: %s\n", cmd.command,
                      (cmd.help) ? cmd.help : "(unknown)");
        }
    }

    struct Command
    {
        const element_t *command;
        Handler handler;
        const char *help = nullptr;

        bool handle(CommandLine &cli)
        {
            bool should_handle =
                strcmp(command, cli.get_command().c_str()) == 0;

            if (should_handle)
            {
                handler(cli);
            }

            return should_handle;
        }
    };

    std::array<Command, max_commands> commands;
    std::size_t command_index;
};

using CommandLineApp = ElementCommandLineApp<>;

} // namespace Coral
