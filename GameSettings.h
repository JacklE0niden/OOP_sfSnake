// GameSettings.h
#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

enum class Difficulty
{
    Easy,
    Medium,
    Hard,
    Insane
};

// std::string difficultyToString(Difficulty difficulty) {
//     switch (difficulty) {
//         case Difficulty::Easy:
//             return "Easy";
//         case Difficulty::Medium:
//             return "Medium";
//         case Difficulty::Hard:
//             return "Hard";
//         case Difficulty::Insane:
//             return "Insane";
//         default:
//             return "Unknown";
//     }
// }

#endif // GAME_SETTINGS_H