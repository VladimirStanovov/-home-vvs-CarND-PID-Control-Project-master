# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## The effect each of the P, I, D components

This repository contains my solution to Udacity SDC ND project for PID control. The PID parameters should be tuned/selected by some optimization technique, to make it possible for the vehicle in the simulator drive safely along the track.

First of all, I've tried to tune parameters by hand, but this was not successful, then I implemented the twiddle algorithm, which is a simple zero-order local optimization technique, but this also didn't give any good results. After several days of testing I've figured out that the hardware was the problem: a low level graphics cannot run the simulator fast enough, so the vehicle starts oscillating, and it appears to be almost impossible to tune the parameters, unless the speed is lower than 5 MPH.

After I fixed the hardware problem (added a discrete video adapter), I was able to successfully run the simulator with gains, given in the course: [0.2, 0.004, 3] for p, i and d part respectively. At first, I expected the integral part to be of small importance, as the vehicle does not seem to have a systematic drift from the zero position. However, integral part appeared to be very effective at making the control smoother, i.e. eliminating oscillations provided by both proportional and differential parts. So I ended up with the following set of parameters: [0, 0.015, 1].

After this I've added the PID controller for throttle control, which included only proportional and integral part: [0.5, 0.001, 0]. This was relatively simple and I did just several experiments for desired speed = 30.

My implementation of twiddle algorithm included error calculation, which considered sum of square errors of CTE, plus a large penalty depending on how early the vehicle went off the track or stopped. This penalty helped avoiding situations when a set of parameters that simply made vehicle drive off track in the beginning received small average squared error just because there was only a couple of measurements with large error.

I've experimented with different initial positions for twiddle, and it appeared that the algorithm is very sensitive to them. For example, I was able to receive the following optimized parameter sets: [0.1848, 0, 1.63495], for the case with zero changes in integral part, [0.1561, 0.001191, 1.0674] for the case when all parameters are changed and start from [0.2, 0.004, 3] and [0.007927, 0.01445, 0.999345] for the case when the initial parameters were [0, 0.015, 1]. Although all of these variants perform well, I personally liked the [0.007927, 0.01445, 0.999345] more. This brought me to and idea that probably checking all sets of parameters in a certain range with, say, steps of [0.01,0.001,0.1] could give nice results, which could be afterwards improved by twiddle.

Here are the small videos of how hand-tuned:
https://www.youtube.com/watch?v=kVM8x1ZBUTw
and twiddle-tuned parameters perform:
https://www.youtube.com/watch?v=A0hehjoo1iA
