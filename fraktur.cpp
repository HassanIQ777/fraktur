#include <iostream>
#include <string>
#include <unordered_map>

// Appends one Unicode codepoint to `out`, hand-rolled as raw UTF-8 bytes.
// Why not just use std::wcout and let the standard library deal with it?
// Because that needs (a) wchar_t to agree on a size across platforms
// (it doesn't — 2 bytes on Windows, 4 on Linux/Mac) and (b) a working
// UTF-8 locale to be installed and imbue()'d correctly (it often isn't,
// especially on Termux/Android — exactly what bit us last time). A
// hand-rolled UTF-8 encoder has zero dependencies on any of that.
void append_utf8(std::string &out, char32_t cp) {
  if (cp <= 0x7F) {
    out += static_cast<char>(cp);
  } else if (cp <= 0x7FF) {
    out += static_cast<char>(0xC0 | (cp >> 6));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  } else if (cp <= 0xFFFF) {
    out += static_cast<char>(0xE0 | (cp >> 12));
    out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  } else { // 4-byte range — home to every Fraktur letter but our 5 fugitives
    out += static_cast<char>(0xF0 | (cp >> 18));
    out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
    out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
    out += static_cast<char>(0x80 | (cp & 0x3F));
  }
}

// Converts ASCII text to Fraktur, returned as a plain UTF-8 std::string —
// no std::wstring, no std::wcout, no locale imbue(). Print it with an
// ordinary std::cout; your terminal already speaks UTF-8 natively.
std::string to_fraktur(const std::string &text) {
  static const std::unordered_map<char, char32_t> fraktur_map = {
      // --- Uppercase: 21 live in the math block, 5 are runaways below ---
      {'A', 0x1D504},
      {'B', 0x1D505},
      {'C', 0x212D}, // fugitive #1 (Black-Letter Capital C)
      {'D', 0x1D507},
      {'E', 0x1D508},
      {'F', 0x1D509},
      {'G', 0x1D50A},
      {'H', 0x210C}, // fugitive #2 (Black-Letter Capital H)
      {'I', 0x2111}, // fugitive #3 (Black-Letter Capital I)
      {'J', 0x1D50D},
      {'K', 0x1D50E},
      {'L', 0x1D50F},
      {'M', 0x1D510},
      {'N', 0x1D511},
      {'O', 0x1D512},
      {'P', 0x1D513},
      {'Q', 0x1D514},
      {'R', 0x211C}, // fugitive #4 (Black-Letter Capital R)
      {'S', 0x1D516},
      {'T', 0x1D517},
      {'U', 0x1D518},
      {'V', 0x1D519},
      {'W', 0x1D51A},
      {'X', 0x1D51B},
      {'Y', 0x1D51C},
      {'Z', 0x2128}, // fugitive #5 (Black-Letter Capital Z)

      // --- Lowercase: no holes here, the block behaves itself ---
      {'a', 0x1D51E},
      {'b', 0x1D51F},
      {'c', 0x1D520},
      {'d', 0x1D521},
      {'e', 0x1D522},
      {'f', 0x1D523},
      {'g', 0x1D524},
      {'h', 0x1D525},
      {'i', 0x1D526},
      {'j', 0x1D527},
      {'k', 0x1D528},
      {'l', 0x1D529},
      {'m', 0x1D52A},
      {'n', 0x1D52B},
      {'o', 0x1D52C},
      {'p', 0x1D52D},
      {'q', 0x1D52E},
      {'r', 0x1D52F},
      {'s', 0x1D530},
      {'t', 0x1D531},
      {'u', 0x1D532},
      {'v', 0x1D533},
      {'w', 0x1D534},
      {'x', 0x1D535},
      {'y', 0x1D536},
      {'z', 0x1D537}};

  std::string result;
  result.reserve(text.size() * 4);
  for (char c : text) {
    auto it = fraktur_map.find(c);
    if (it != fraktur_map.end()) {
      append_utf8(result, it->second);
    } else {
      result += c;
    }
  }
  return result;
}

int main() {
  std::cout << "Enter text to convert to Fraktur (':' to quit):\n";

  std::string input;
  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, input))
      break;
    if (!input.empty() && input[0] == ':')
      break;

    std::cout << to_fraktur(input) << "\n";
  }

  std::cout << "\nThanks for using Fraktur by HassanIQ777\n";
  return 0;
}