## Name
Joined primitives

## What this tests
Two transparent triangles forming a rectangle

## Expected result
A white screen with no artifacts at the triangle edges

## Why
There are cases where two triangles are used to form a rectangle and when they become transparent, if the triangle spans are not perfect, can produce blending artifacts at the edges. An example is pressing start at the Mario face in SM64, which fades into a white screen using two triangles