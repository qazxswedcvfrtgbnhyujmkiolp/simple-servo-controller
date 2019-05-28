# simple-servo-controller

This is a very simple servo control algorithm, designed to use the Motor shield library but easily portable to other situations. It uses two "stages" to better control a servo. The first stage quickly moves the servo close to the setpoint, then the second stage finishes moving it to the exact point. Using a PID controller will make more sense in most situations, but this algorithm might be easier to understand for new programmers.
