# HEW2024
二年生のHEW用

------------[コードの大まかな流れ]-------------------

main(みんな大好きメイン関数)

↓

GameProcess(ゲームの大まかな流れ)

↓

GameManager(ゲームの中身)

↓

GameObject			←	Component(機能のベース)		←	いろいろな機能
(コンポーネントを持つ)

-----------------------------------------------------


------------[Componentを追加するなら]-------------------

Componentを継承した○○コンポーネントを作る
↓
