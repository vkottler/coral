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

template <std::size_t depth = default_max_line,
          std::size_t max_args = default_max_args, typename element_t = char,
          class T = PrintfLogger>
class ElementCommandLineApp : public HasLogInterface<T>
{
  public:
    using CommandLine = ElementCommandLine<element_t, T>;
    using Processor = StringCommandProcessor<depth, element_t, max_args>;

    using Handler = std::function<void(CommandLine &)>;

    ElementCommandLineApp(typename Processor::Buffer &input,
                          LogInterface<T> *_log = nullptr)
        : HasLogInterface<T>(_log),
          processor(
              input,
              [this](const element_t **argv, std::size_t argc) {
                  process(argv, argc);
              },
              true /* auto_poll */)
    {
        this->logger = _log;
        add_handler("help", [this](CommandLine &cli) { help(cli); });
    }

    /* interface for registering a command */
    void add_handler(const element_t *command, Handler handler,
                     LogInterface<T> *_log = nullptr)
    {
        this->log(_log, "Added command handler for '%s'.\n", command);

        /* need to figure out a data structure for these */
        (void)handler;
    }

    void process(const element_t **argv, std::size_t argc)
    {
        CommandLine cli(argv, argc, this->logger);

        this->log(nullptr, "process\n");

        /* check for a command handler, otherwise do help */
        help(cli);
    }

  protected:
    Processor processor;

    void help(CommandLine &cli)
    {
        /* dump info about registered commands */
        (void)cli;

        this->log(nullptr, "help command\n");
    }
};

using CommandLineApp = ElementCommandLineApp<>;

} // namespace Coral
