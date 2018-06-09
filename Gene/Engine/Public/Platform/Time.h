// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once
#include <chrono>

namespace gene { namespace platform {
    class Timer {
    private:
        typedef std::chrono::time_point<std::chrono::high_resolution_clock> GameClock;
        
        GameClock m_Start;
        bool m_Running;
    public:
        Timer() : m_Running(false) {}

        void Start();
        void Stop();
        bool Running() { return m_Running; }

        double ElapsedTimeSeconds();
        double ElapsedTimeMs();
    };

	class GameTime {
    private:
        typedef std::chrono::time_point<std::chrono::high_resolution_clock> GameClock;

        float     m_Delta;
        float     m_RunningTime;
        
        GameClock m_StartFrameTime;
        GameClock m_EndFrameTime;
        GameClock m_GameStart;

        bool m_HasGotEndFrameTime;

	public:
        /**
         * Begins the "Running Time" timer and initalises class. No work is done in constructor so in order to
         * start the timer call this function.
         */
        void Start();

        /** The time between StartFrame() and EndFrame() being called in milliseconds. "Delta time" */
        float DeltaInMilliSeconds() const { return m_Delta; }

        /** Returns how long since Init() was called in seconds. */
        float RunningTimeSeconds()  const { return m_RunningTime; }

        /** Utility function to return how long since Init() was called in milliseconds */
        float RunningTimeMilliseconds() const;

        /** Should be called when the frame starts. */
        void  StartFrame();

        /** Should be called when the frame ends. */
        void  EndFrame();

        /** Sleep the current thread for the specified amount of time. */
        void  Sleep(float milliseconds);
	};
}}
