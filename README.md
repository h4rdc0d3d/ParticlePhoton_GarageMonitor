# Particle Photon: Garage Monitor & Controller
[![Waffle.io - Columns and their card count](https://badge.waffle.io/kevinsutton/photon_garage-monitor.svg?columns=all)](https://waffle.io/kevinsutton/photon_garage-monitor)

The intent of this project is to create a system that can be used to watch, alert, and ultimately control the 3 single garage doors at my house.

## The Problem
As a parent of three driving teenagers, I often find my garage doors left open through all hours of the night.  I'm not a trusting person and don't care to wait for an unwelcome visit from a local trouble-maker to help themselves to valuables in the cars or garage.

## The Solution
- MVP1: Use one of my many Particle Photons to monitor the status of all three garage doors and notify me via SMS or email if they are left open for a specified time (i.e. 5-10 minutes) during late-night hours (i.e. 11PM-6:30AM).
  - Execute after a scheduled interval (every minute)
  - Check each Garage Door status (via reed switches) to see if they are open or closed
  - Turn LED light ON when door is OPEN and OFF when door is CLOSED
  - If OPEN and LATE-NIGHT, start counter and increment each run
    - Once counter reaches Alert Threshold, send notifications
- MVP2: Use Cloud functions
  - Check door status
  - Turn lights ON/OFF
  - Mobile integration to Cloud functions
- MVP3: Siri integration to Cloud functions
- MVP4: Open/Close garage doors thru hard-wire connection (via Photon Relay-Shield)
