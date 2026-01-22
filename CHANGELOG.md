# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html), as well as [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/).

> [!WARNING]
> In spite of this project adhering to SemVer, until the first MAJOR version comes out, i.e., until I decide this project is mature enough, MAJOR changes will tick the MINOR counter.  So please stick to this changelog and look for changes which might impact you before migrating.


## [Unreleased]

### Added
### Changed
### Deprecated
### Removed
### Fixed
### Security


## [0.2.1] 2026-01-22

### Fixed
- Print correct log-level according to the logging function used instead of always printing the logga level


## [0.2.0] 2026-01-18

### Added
- Added `logga_lvtostr` function to parse `logga_level_t`s as a `char *`s
- Added this changelog to the project
### Changed
- Moved from a singleton model to a more granular one by adding `logga_t`, which stores state about a logger instance and is passed around in the logga functions
### Fixed
- Added the packaged library as a dependency to the `test` target to rebuild the `test` executable after making changes to `logga.c`
