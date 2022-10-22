# tiny-zip

[![Stargazers][stars-shield]][stars-url]
[![Contributors][contributors-shield]][contributors-url]
[![GPLv3 License][license-shield]][license-url]

A tiny compression program, similar to zip.

## Example usages

```
$ tiny-zip ./tests/1.txt -o ./tests/rez.tzip
[INFO] Compressed ./tests/1.txt
[INFO] Serialized to ./tests/res.tzip

$ tiny-zip ./tests/1.txt --output ./tests/rez.tzip
[INFO] Compressed ./tests/1.txt
[INFO] Saved to ./tests/res.tzip


$ tiny-zip ./tests/1.txt -q
# saved the compressed file as ./tests/1.tzip

$ tiny-zip ./tests/1.txt --quiet

$ tiny-zip -d ./tests/1.tzip
[INFO] Decompressed ./tests/1.tzip
[INFO] Saved to ./tests/1.txt

$ tiny-zip --decompress ./tests/1.tzip -o ./tests/res.txt
[INFO] Decompressed ./tests/1.tzip
[INFO] Saved to ./tests/res.txt
```

Quick testing:

```
tiny-zip ./tests/1.txt -o ./tests/res.tzip
tiny-zip ./tests/res.tzip -o ./tests/res.txt -d
```

| option           | description                 |
| ---------------- | --------------------------- |
| -o, --output     | specify the output filename |
| -q, --quiet      | no info logs                |
| -d, --decompress | decompress a file           |

## Licence

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.txt) © [Stefan Asandei](https://www.stefan-asandei.cf)

[contributors-shield]: https://img.shields.io/github/contributors/NikolaTesla13/tiny-gzip.svg?style=social
[contributors-url]: https://github.com//NikolaTesla13/tiny-gzip/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks//NikolaTesla13/tiny-gzip.svg?style=social
[forks-url]: https://github.com/NikolaTesla13/tiny-gzip/network/members
[stars-shield]: https://img.shields.io/github/stars/NikolaTesla13/tiny-gzip.svg?style=social
[stars-url]: https://github.com/NikolaTesla13/tiny-gzip/stargazers
[issues-shield]: https://img.shields.io/github/issue/NikolaTesla13/tiny-gzip.svg?style=social
[issues-url]: https://github.com/NikolaTesla13/tiny-gzip/issues
[license-shield]: https://img.shields.io/github/license/NikolaTesla13/tiny-gzip.svg?style=social
[license-url]: https://github.com/NikolaTesla13/tiny-gzip/blob/master/LICENSE

```

```
