
#include <rendercore/ChronoTimer.h>


namespace rendercore
{


ChronoTimer::ChronoTimer(bool startNow, bool autoUpdate)
: m_paused(true)
, m_autoUpdate(autoUpdate)
, m_t0(clock::now())
, m_tp(m_t0)
, m_t1(m_t0)
, m_offset(Duration::zero())
, m_elapsed(Duration::zero())
{
    if (startNow) {
        start();
    }
}

ChronoTimer::~ChronoTimer()
{
}

void ChronoTimer::update()
{
    m_t1 = m_paused ? m_tp : clock::now();

    const auto delta = m_t1 - m_t0;
    m_elapsed = delta + m_offset;
}

bool ChronoTimer::paused() const
{
    return m_paused;
}

void ChronoTimer::start()
{
    if (!m_paused) {
        return;
    }

    const time_point t2 = clock::now();
    m_offset -= t2 - m_tp;

    m_t1 = t2;
    m_paused = false;
}

void ChronoTimer::pause()
{
    if (m_paused) {
        return;
    }

    m_tp = clock::now();
    m_paused = true;
}

void ChronoTimer::stop()
{
    pause();
    reset();
}

void ChronoTimer::reset()
{
    m_offset  = Duration::zero();
    m_elapsed = Duration::zero();

    m_t0 = clock::now();
    m_t1 = m_t0;
    m_tp = m_t0;
}

ChronoTimer::Duration ChronoTimer::elapsed() const
{
    if (m_autoUpdate) {
        const_cast<ChronoTimer*>(this)->update();
    }

    return m_elapsed;
}

void ChronoTimer::setAutoUpdating(bool autoUpdate)
{
    m_autoUpdate = autoUpdate;
}

bool ChronoTimer::autoUpdating() const
{
    return m_autoUpdate;
}


} // namespace rendercore
