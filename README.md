# 2D Ray-Optics Sandbox

## Project

An interactive 2D ray-optics sandbox (built with **raylib**) where you place mirrors, refractive discs (lenses), and light sources that emit many rays. Rays are traced in real time; they reflect and refract according to basic geometric optics (Snell’s law, Fresnel split optional). The project is intentionally small, visual, and rich in low-level C systems work so you learn pointers, manual memory management, and common data structures while producing something fun to tinker with and show.

## Goal

* Build a clean, modular C codebase that implements ray casting, reflection, and refraction in 2D.
* Provide a responsive interactive UI (raylib) for placing geometry and tuning parameters.
* Practice and demonstrate core C skills: pointers, `malloc`/`calloc`/`free`, linked lists, trees/quadtrees, tries for autocomplete, and hash tables for presets.
* Learn good software engineering habits for low-level C code (memory ownership, testing, tooling).

## Scope

**MVP (finishable quickly)**

* Single file/segment mirrors and circular refractive regions.
* Point light sources that emit a fan of rays.
* Ray tracing with limited recursion (reflections/refractions), intensity attenuation.
* Simple UI to add/remove primitives, toggle debug draw (show ray paths).
* Brute-force intersections (no acceleration) and a small demo preset.

**Next / Stretch**

* Quadtree acceleration for intersection queries.
* Fresnel reflection/transmission and intensity bookkeeping.
* Console with trie autocompletion + hash table presets (named scenes / materials).
* Export frames or record “photon paths” with fading visualization.
* Performance tuning and Valgrind/ASAN cleanup.

## Repo layout (suggested)

```
src/
  main.c           // app entry, UI loop
  ray.c ray.h      // ray struct & tracing logic
  geom.c geom.h    // segments, circles, intersections
  quadtree.c/.h    // spatial acceleration (optional)
  trie.c/.h        // console autocomplete
  hashtable.c/.h   // presets, materials
  graphics.c/.h    // raylib helpers & debug drawing
Makefile
README.md
presets/
```

---

## TODO: focused learning checklist (what to practice & good practices)

Below are the exact C skills you asked for, with practical notes and recommended best practices for each. Treat these as explicit learning targets to implement, test, and master while building the sandbox.

### 1. Pointers

* **What to do:** Use pointers for dynamic objects (rays, primitives, tree nodes). Pass pointers to functions instead of copying large structs.
* **Good practice:** Maintain clear ownership: who `malloc`s, who `free`s. Prefer `const` for pointers that should not mutate data. Check for `NULL` before dereferencing.

### 2. Dynamic memory (`malloc`, `calloc`, `realloc`, `free`)

* **What to do:** Allocate pools for rays, dynamic arrays for primitives, and nodes for quadtrees and trie.
* **Good practice:** Check allocation results and handle failures. Use `calloc` when you need zeroed memory (e.g., nodes). Free every allocation and use Valgrind / ASAN to verify no leaks. Encapsulate alloc/free in small APIs (e.g., `ray_pool_create()` / `ray_pool_destroy()`).

### 3. Linked lists (and reversing/freeing them)

* **What to do:** Use chained lists for per-cell buckets, or to store a ray’s path segments. Implement prepend, reverse, traversal, and proper freeing.
* **Good practice:** Keep list node structure minimal, write a single `list_free(head, free_data_cb)` utility, and avoid deep recursion when freeing long lists.

### 4. Trees / Quadtrees (and tries)

* **What to do:** Implement a quadtree that stores primitive indices or small vectors for fast spatial queries. Implement a trie for the in-app console autocomplete.
* **Good practice:** Keep tree node allocation localized (factory functions), cap leaf capacities before subdivision, and provide a `destroy` function that frees children recursively. For trie, avoid storing large strings in nodes — store only structure and mark word ends; free recursively.

### 5. Hash maps / hash tables / dictionaries

* **What to do:** Use a simple chained hash table to map preset names → scene/state structs and material names → optical parameters.
* **Good practice:** Implement or reuse a robust hash (e.g., `djb2` or `xxhash`), handle collisions with chaining, and provide functions to `set/replace/get/remove`. Decide and document memory ownership for keys and values (who duplicates strings, who frees them).

---

## Practical engineering & testing tips (apply these as you work)

* **Module boundaries:** Keep each data structure in its own `.c/.h` pair with a small public API.
* **Error handling:** Check return values for I/O and allocations. Fail early with informative `perror` or logs.
* **Memory tools:** Run Valgrind and AddressSanitizer regularly; fix leaks and invalid accesses immediately.
* **Small steps & tests:** Start with ray→segment intersection unit tests (text-mode). Add visual tests later.
* **Determinism:** Keep physics deterministic for reproducible debugging (fixed timestepping).
* **Code style:** Use consistent formatting, small functions, and short files. Comment ownership semantics and invariants.
* **Performance:** Profile hotspots (ray tracing loops) before premature optimization. Reuse buffers (object pools) instead of repeated alloc/free in inner loops.

---

## Quick start suggestion

1. Implement and test ray→segment and ray→circle intersections (text only).
2. Add a simple ray pool and render rays with raylib (one frame per second) to verify visuals.
3. Add reflection, then refraction (Snell’s law).
4. Add a quadtree and swap brute force for accelerated queries.
5. Add trie console + hash table presets once main loop and UI are stable.
