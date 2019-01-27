
# rendercore

This library has the purpose to provide basic building blocks for real-time
rendering applications using graphics APIs like OpenGL or Vulkan. It provides
basic structures and processes, which are always needed in such applications,
such as running a main loop, managing rendering contexts, or controlling the
rendering and animation logic, and provides clear interfaces for embedding
rendering code into specific system or UI frameworks, such as Qt or GLFW.

It attempts to "get the basics right", i.e., omit typical problems and
pitfalls which are seen in many rendering frameworks and engines (e.g.,
a messed up main loop, chaotic initialization/deinitialization structures,
not taking multithreading into account, or inflexible handling of
continuous/non-continuous rendering and animation).

This library is therefore not meant as a full rendering engine, but rather
as the basis for one.


## Libraries

### rendercore

This library contains basic building blocks for real-time rendering
applications, which are not dependent on a specific API, UI framework,
or system.

### rendercore-glfw

This library contains an implementation for GLFW. It provides the structure
for creating windows and contexts with GLFW and embedding the rendering
structure provided by rendercore.


## Design Overview

This sections describes typical problems often encountered in rendering
frameworks, and the design decisions made in this library to avoid them.

### Rendering contexts

[TODO]

### Mainloop

The mainloop is the backbone of any real-time rendering application. It runs
continuously and listens to events from the UI system, such as keyboard or
mouse events, or commands to redraw a window's content. Usually, the mainloop
in a UI application should not run actively all the time, but fetch all
incoming events, process them, and then go to sleep. The system will then
wake up the mainloop as soon as new events have arrived.

In many real-time rendering code, though, the mainloop is written in a way
that is continuously polls for events and often also renders all the time.
This results in 100% CPU load and is often unnecessary, as there is not
always an animation running or an interaction in process. Therefore,
rather than letting the mainloop run continuously all the time, the
rendering and interaction code should be able to trigger a new rendering
whenever it is needed, but when it is not needed, the mainloop should go
to sleep by default.

In this library, the main loop is implemented in the following way:
- By default, the mainloop processes all open events and then goes to sleep.
- When a draw-event occurs, it invokes the renderer exactly once.

[TODO]

### Continuous rendering

By default, the rendering is non-continuous, so a rendering is only triggered
when a redraw-event by the windowing system has arrived, e.g., because the
window has been resized.

[TODO]

### Animation

[TODO]

### Interaction

[TODO]
