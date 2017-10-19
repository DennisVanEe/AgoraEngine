# AgoraEngine

A still-in-progress game engine written in C++.
This is the accumulation of everything I have learned over the years of writing game engines. The engine is made (as reasonably possible)
from scratch. The main goal of the engine is to be a high-performance engine designed specifically with city-building like games in mind.
The engine has a custom math library written with SIMD, a "no allocation during gameplay" memory allocotation model, and uses a custom
file format for quickly loading preprocessed (with the ASSIMP library) models and other resources.
