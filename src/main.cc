
/// @brief - Simplistic clone of the eponymous city building game.

#include "App.hh"
#include "AppDesc.hh"
#include "IsometricViewFrame.hh"
#include "TopViewFrame.hh"
#include <core_utils/CoreException.hh>
#include <core_utils/log/Locator.hh>
#include <core_utils/log/PrefixedLogger.hh>
#include <core_utils/log/StdLogger.hh>

int main(int /*argc*/, char ** /*argv*/)
{
  // Create the logger.
  utils::log::StdLogger raw;
  raw.setLevel(utils::log::Severity::DEBUG);
  utils::log::PrefixedLogger logger("pge", "main");
  utils::log::Locator::provide(&raw);

  try
  {
    logger.notice("Starting application");

    auto tiles  = pge::CenteredViewport({5.0f, 5.0f}, {18.0f, 13.5f});
    auto pixels = pge::TopLeftViewport({0.0f, 0.0f}, {800.0f, 600.0f});

    pge::CoordinateFramePtr frame;
    auto useIsometric = true;
    if (useIsometric)
    {
      frame = std::make_shared<pge::IsometricViewFrame>(tiles, pixels);
    }
    else
    {
      frame = std::make_shared<pge::TopViewFrame>(tiles, pixels);
    }

    pge::AppDesc ad = pge::newDesc(olc::vi2d(800, 600), frame, "pharaoh");
    pge::App demo(ad);

    demo.Start();
  }
  catch (const utils::CoreException &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
  }
  catch (const std::exception &e)
  {
    logger.error("Caught internal exception while setting up application", e.what());
  }
  catch (...)
  {
    logger.error("Unexpected error while setting up application");
  }

  return EXIT_SUCCESS;
}
