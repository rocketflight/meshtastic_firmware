#pragma once

#include "freertosinc.h"

namespace concurrency {

/**
 * @brief Base threading
 */
class Thread
{
  protected:
    TaskHandle_t taskHandle = NULL;

    /**
     * set this to true to ask thread to cleanly exit asap
     */
    volatile bool wantExit = false;

  public:
    void start(const char *name, size_t stackSize = 1024, uint32_t priority = tskIDLE_PRIORITY);

    virtual ~Thread() { vTaskDelete(taskHandle); }

    uint32_t getStackHighwaterMark() { return uxTaskGetStackHighWaterMark(taskHandle); }

  protected:
    /**
     * The method that will be called when start is called.
     */
    virtual void doRun() = 0;

  private:
    static void callRun(void *_this);
};

} // namespace concurrency
