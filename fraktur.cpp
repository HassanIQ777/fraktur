#include <iostream>
#include <string>
#include <unordered_map>

// Function to convert text to Fraktur
std::wstring to_fraktur(const std::string &text) {
  // Mapping Latin characters to Fraktur Unicode code points.
  //
  // Fun fact nobody asked for: the Mathematical Alphanumeric Symbols block
  // is NOT a clean, unbroken strip of 26 letters. Five capitals — C, H, I,
  // R, Z — were quietly evicted from the block because older "black-letter"
  // symbols already squatted those five slots decades earlier (ℜ for the
  // reals, ℑ for the imaginaries, ℨ for... apparently just vibes). Unicode
  // didn't want two codepoints rendering the same glyph, so it left five
  // holes in the math block and pointed those letters at the old symbols
  // instead. Walk the block pretending it's contiguous (like the original
  // code did) and you silently drift off the rails the moment you pass C —
  // which is exactly what was happening here.
  static const std::unordered_map<char, wchar_t> fraktur_map = {
      // --- Uppercase: 21 live in the math block, 5 are runaways below ---
      {'A', L'\U0001D504'},
      {'B', L'\U0001D505'},
      {'C', L'\U0000212D'}, // fugitive #1 (was in the block, now Black-Letter
                            // Capital C)
      {'D', L'\U0001D507'},
      {'E', L'\U0001D508'},
      {'F', L'\U0001D509'},
      {'G', L'\U0001D50A'},
      {'H', L'\U0000210C'}, // fugitive #2 (Black-Letter Capital H)
      {'I', L'\U00002111'}, // fugitive #3 (Black-Letter Capital I)
      {'J', L'\U0001D50D'},
      {'K', L'\U0001D50E'},
      {'L', L'\U0001D50F'},
      {'M', L'\U0001D510'},
      {'N', L'\U0001D511'},
      {'O', L'\U0001D512'},
      {'P', L'\U0001D513'},
      {'Q', L'\U0001D514'},
      {'R', L'\U0000211C'}, // fugitive #4 (Black-Letter Capital R)
      {'S', L'\U0001D516'},
      {'T', L'\U0001D517'},
      {'U', L'\U0001D518'},
      {'V', L'\U0001D519'},
      {'W', L'\U0001D51A'},
      {'X', L'\U0001D51B'},
      {'Y', L'\U0001D51C'},
      {'Z', L'\U00002128'}, // fugitive #5 (Black-Letter Capital Z)

      // --- Lowercase: no holes here, the block behaves itself ---
      {'a', L'\U0001D51E'},
      {'b', L'\U0001D51F'},
      {'c', L'\U0001D520'},
      {'d', L'\U0001D521'},
      {'e', L'\U0001D522'},
      {'f', L'\U0001D523'},
      {'g', L'\U0001D524'},
      {'h', L'\U0001D525'},
      {'i', L'\U0001D526'},
      {'j', L'\U0001D527'},
      {'k', L'\U0001D528'},
      {'l', L'\U0001D529'},
      {'m', L'\U0001D52A'},
      {'n', L'\U0001D52B'},
      {'o', L'\U0001D52C'},
      {'p', L'\U0001D52D'},
      {'q', L'\U0001D52E'},
      {'r', L'\U0001D52F'},
      {'s', L'\U0001D530'},
      {'t', L'\U0001D531'},
      {'u', L'\U0001D532'},
      {'v', L'\U0001D533'},
      {'w', L'\U0001D534'},
      {'x', L'\U0001D535'},
      {'y', L'\U0001D536'},
      {'z', L'\U0001D537'}};

  std::wstring result;
  result.reserve(text.size()); // cheap trick: we know the upper bound, no
                               // reason to let the string reallocate mid-flight
  for (char c : text) {
    auto it = fraktur_map.find(c);
    result += (it != fraktur_map.end()) ? it->second : static_cast<wchar_t>(c);
  }
  return result;
}

int main() {
  std::cout << "Enter text to convert to Fraktur (':' to quit):\n";
  std::wcout.imbue(std::locale(""));

  std::string input;
  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, input))
      break; // EOF / stream died — bail instead of looping forever
    if (!input.empty() && input[0] == ':')
      break;

    std::wcout << to_fraktur(input) << L"\n";
  }

  std::cout << "\nThanks for using Fraktur by HassanIQ777\n";
  return 0;
}