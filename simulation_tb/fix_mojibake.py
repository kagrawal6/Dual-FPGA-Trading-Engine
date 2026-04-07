"""Fix double-encoded UTF-8 in .sv files (arrow, em dash, approx). Run from repo root: python simulation_tb/fix_mojibake.py"""
import pathlib

# Mojibake from UTF-8 punctuation re-encoded as UTF-8 again (common after bad copy/paste or script).
MOJIBAKE = [
    (b"\xc3\xa2\xe2\x80\xa0\xe2\x80\x99", b" -> "),  # was right arrow
    (b"\xc3\xa2\xe2\x82\xac\xe2\x80\x9d", b" - "),  # was em dash
    (b"\xc3\xa2\xe2\x80\xb0\xcb\x86", b" ~ "),  # was almost-equal
]

root = pathlib.Path(__file__).parent
for p in sorted(root.glob("*.sv")):
    data = p.read_bytes()
    new = data
    for a, b in MOJIBAKE:
        new = new.replace(a, b)
    if new != data:
        p.write_bytes(new)
        print("fixed:", p.name)

# Collapse double spaces left next to arrow/dash/tilde replacements.
for p in sorted(root.glob("*.sv")):
    t = p.read_text(encoding="utf-8")
    orig = t
    while "  ->  " in t:
        t = t.replace("  ->  ", " -> ")
    t = t.replace("  ~  ", " ~ ")
    while "  -  " in t:
        t = t.replace("  -  ", " - ")
    if t != orig:
        p.write_text(t, encoding="utf-8", newline="\n")
        print("spaced:", p.name)
