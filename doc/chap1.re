= 一日目
== 目的

 * 「マインスイーパ」をAndroidアプリとして実装してみる
 * 前提: JavaとEclipseの扱いが少し分かること
 ** Javaで@<code>{if}, @<code>{for}といった概念が分かる。
 *** メソッド等についても書き方が分かる
 ** EclipseとAndroid SDKのインストール、ADTの準備ができている
 ** EclipseでAndroidプロジェクトのインポートが出来ること

== 「マインスイーパ」とは

 * http://goo.gl/yBHU77 (マインスイーパ - Wikipedia)
 * http://minesweeperonline.com/#beginner
 ** 画像を@<img>{minesweeper}に示す。
 * このゲームをAndroid上で動くように作ってみる。

//image[minesweeper][マインスイーパ][]{
//}

== 「マインスイーパ」の仕様

//quote{
仕様（しよう、英: Specification）とは、材料・製品・サービスが明確に満たさなければならない要求事項の集まりである。仕様を記述した文書を仕様書と呼ぶ。
(仕様 - Wikipedia)
//}

 * 今回の「仕様」は厳密である必要はない
 ** 他人に作ってもらうわけではないので、曖昧な部分があっても自分が処理できる
 * 概要から詳細へ
 ** どういうゲームであって欲しいか
 ** ゲームとして、どのような要素が必要か
 ** どのような画面にして、どこをクリックしたらどう動くのか
 * 簡単なゲームなら頭の中である程度まとめ時点で実装を始められる
 ** 今回、どういうゲームかは明らかなので、それを達成する要素から考えていく。
 ** 難しい場合は、「仕様書」のレベルで考える要素が多い。

=== どのような要素が必要か

 * ボタンが格子状（マス目状）に配置されている
 ** 一部は爆弾で、他は空
 * マスをクリックすると、爆弾かどうかが判明する
 ** 何もないところと爆弾のあるところ
 ** 何もないところでは「数字」が表示されることもある
 *** 数字は周囲8マスの爆弾の数を表している
 * 爆弾を避けて全て掘れたら「クリア」
 * 今回は実装をしないが、本物には以下のような要素もある
 ** 右クリックで「旗」を立てられる
 ** マウスのボタンを2つ同時にクリックすると、そのマス目の周囲をクリックしたことになる
 ** 最初にクリックしたマス目は爆弾にならない
 *** 当初のWindows版にはあるが、そうでないケースもあり、イライラさせられる

要素が分かったら、それを「実装」する

 * implement ... 実装する
 * implementation ... 実装 (実装した結果、どうやって実装したか)

=== Android上で実装する場合、何が必要か

 * 「ゲームの流れ」を考えながら、何が必要かを考える
 ** 「構成要素」と「ゲームの流れ」でアプリの捉え方が少し違う

それはともかく、何が必要か

 * 「最初に」爆弾がどこにあるかを決める
 ** ユーザに「爆弾が見えない」格子状の画面を表示する
 * ユーザのクリックに応じて……
 ** 爆弾でなければ開く
 ** 全部開いたら「クリア」、爆弾なら「ゲームオーバー」
 ** （細かい点を除くと、両方共「ゲームオーバー」でもいい）

ここまで、マインスイーパの動作イメージとしては正しいが、
まだ実装するのに必要な情報が足りない。
「実装」出来るくらいまで、少し細かく考えていく。

プログラマは最終的に動作の細部まで理解する必要がある。

 * 盤面のサイズを 8x8 固定とする
 * 爆弾の数も固定とする
 * 「最初は」爆弾の配置も固定とする
 ** 今回のトレーニングでは、ひと通り実装した後、ランダムに配置する方法を考える
 * ユーザが特定のマス目をクリックしたら「爆弾」かそうでないかを判定する
 * 「終了」したら、「ゲームオーバー」であることをユーザに伝える
 ** 「終了」の条件1: 爆弾をクリックした
 ** 「終了」の条件2: 爆弾以外の全てのマス目を開いた
 * 次のゲームを開始できるように、リセットボタンを表示しておく
 ** リセットボタンを押したら、盤面をリセットして最初に戻る
 * 旗や両ボタンクリックは今回はサポートしない
 * ちなみに、スマホでは「終了」ボタンは要らないので仕様で考える必要もない
 ** 但し、高度なゲームでは「中断」については考える必要がある

== アプリを動かしてみる

まず目標を理解した上で、何でもいいからアプリを動かしてみる。

アプリケーション（アプリ）のプロジェクトは@<code>{src/} ディレクトリにある。

==== 使用するツール類の概説（復習）

 * Eclipse
 ** http://ja.wikipedia.org/wiki/%E7%B5%B1%E5%90%88%E9%96%8B%E7%99%BA%E7%92%B0%E5%A2%83
 ** 統合開発環境: ソフトウェア開発に必要な複数のツールをまとめたソフトウェア
 *** エディタ: 何かを編集するためのソフト。メモ帳のお化けみたいなもの
 *** コンパイラ: ソースコードから実際のソフトウェアとして動作する実行コードを生成するもの
 *** デバッガ: ぼっこわれた時にどこが壊れたか、どうやって壊れたかを調べる (デバッグ) ためのツール
 ** 便利機能がたくさんある -> 技術者はエディタの機能に慣れたり、機能を追加したりもする
 * Android SDK
 ** Androidのソフトウェア開発を行うための「ソフトウェア開発キット」
 * ADT Plugin for Eclipse... Android Developer Tools
 ** Eclipseは色々なソフトウェア開発に使う
 ** Android SDKとセットで用意することで「Eclipse上でAndroidアプリの開発を行えるようにする」ツールとなる。

=== アプリの構造を（一部）理解する

今回のサンプルプロジェクトでは、本トレーニングのステップに応じた実装結果が含まれている。

==== Activity / Fragment

 * 画面を表示するための機能。
 ** 「マインスイーパ」実行中、一つのActivity、一つのFragmentだけが存在する
 * 今回のサンプルプロジェクトにはActivityの実装が複数入っている@<img>{activities}
 ** トレーニングのステップに応じた実装
 ** 一つだけ画面として表示する
 ** すぐに説明する@<code>{AndroidManifest.xml}でどれか一つを指定すると、各ステップの画面を見ることが出来る
 ** 自分で実装せずに次のステップに移動してもOK

//image[activities][Activityの実装が階層化されたフォルダに含まれている][]{
//}

==== AndroidManifest.xml

 * このアプリ全般に関する情報が記載されている
 ** アプリ名は何か
 ** アイコンに使う画像はどれか
 ** どういうAndroidデバイスにインストールしてもいいのか
 ** 端末のどういう機能を使ってもいいのか（Permission）
 *** 最近のスマホの情報流出に関わる重要事項。でも今回は関係がない。

===== 今回変更するのは @<code>{android:name} の部分のみ

具体的には以下のような部分の@<code>{android:name=""}のダブルクオートで囲われている部分だけ。

//list[android_manifest_app_name][@<code>{AndroidManifest.xml}の該当部分]{
<activity
  android:name="com.example.training.MainActivityDay1_0_Start"
  android:label="@string/app_name" >
  <intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>
</activity>
//}

 * 意味は「最初に起動する@<code>{Activity}はどれか」
 ** アプリのアイコンをクリックした際に開く画面を指定できる
 ** 今回のトレーニングでは一番重要な場所

==== その他の要素

 * @<code>{src/} ディレクトリ
 ** （分かりづらいが、このアプリプロジェクトの含まれている@<code>{src/}とは別）
 ** ソースコード == javaファイルは個々に収まる
 ** 一般的に、source code の一部を引っ張って"src"としてソースコードを収めることがよくある
 * @<code>{res/} ディレクトリ
 ** リソース (resource) の略で、画像データや文字列データを保存する
 ** 今回はほとんど扱わないが、デバイスの大きさに合わせて複数の画像データが必要になったりする。
 * @<code>{res/layout/}
 ** @<code>{res/}に含まれるリソースの中でも「レイアウト」と呼ばれるものを保存する。
 ** 使い方は後述する

== アプリを実行する

（チェックポイント: @<code>{MainActivityDay1_0_Start.java}）

 * 今回は「エミュレータ」を用いる
 ** emulator -> emulate = 模倣する、真似する
 ** パソコンの中で気軽に実験出来る
 ** 動作がとても遅い
 ** GPSやカメラといった機構を使いづらい
 ** その他色々制約がある
 * 実機にアプリを導入できれば、直接実行することも可能
 ** 実機 ... 本物の端末
 ** 使っているソースコードは同じもの
 * EclipseでRun -> Runを実行する
 * エミュレータは起動しっぱなしにしておこう
 ** エミュレータ自体の起動が非常に遅い。人生は短い

=== 色々試してみよう

 * 今回のトレーニングのステップに沿った@<code>{Activity}が複数収録されている
 * 切り替えることで、特定のステップの画面を見ることが出来る
 * 「チェックポイント」に@<code>{Activity}名が記載されているので@<code>{AndroidManifest.xml}の@<code>{app:name=""}のダブルクォート内を変更して、再度実行する
 ** 正確にこのドキュメントのステップ毎にはなっていない

=== 「信頼されていない」アプリ

開発中のアプリを実機にインストールする場合、
設定画面「提供元不明のアプリ」にチェックを入れる必要がある。@<img>{untrusted-source}

//image[untrusted-source][提供元不明のアプリ][scale=0.2]{
//}

 * 開発中のアプリは、同じソースコードを使っても、デバイスから「信頼」はされていない
 ** 言ってみれば不正ソフトウェアにちょっと近い領域のアプリ
 ** 「信頼されている」とは、すなわち「署名されている」アプリのこと
 ** 「署名」 ... アプリ開発で印鑑を押すようなもの。今回は省略
 *** 正式にGoogleのWebサイト上で販売したりする場合は必須になる
 * 注意: これを行うと、Googleの公式マーケット以外から提供された危険なアプリをインストールしても気づかない

=== 「空白」「改行」「全角文字」に注意

 * プログラムの中では意味が当然違う。
 ** 特に「全角」はエラーになる (エラーと警告の違いについては後述)
 * おまけ: http://ja.wikipedia.org/wiki/Whitespace
 ** http://compsoc.dur.ac.uk/whitespace/count.ws

=== 脱線: プログラマは「0から始める」のがお好き

 * 慣習に若干近い……？
 ** 「複数のオリジンが混在する身近な例として、日時があげられる。年・月・日は1オリジンであるが、時・分・秒は0オリジンである。」
 ** http://ja.wikipedia.org/wiki/%E3%82%AA%E3%83%AA%E3%82%B8%E3%83%B3
 * Androidアプリで使われるJava言語では 0-origin を用いる
 * 今回は全く関係ないがメモリアドレスに関わる計算をする際の名残？と考えると分かりやすい
 ** addr+0 は先頭 (今ではlst[1]が最初でも不整合は生じない)
 * ファイル名でも1-originと0-originが混ざってますね (day1, day2 に対して _0_)

== アプリに部品を配置する

初期状態となる@<code>{layout/mine_fragment_day1_0.xml}の中身は以下の通り。

//list[mine_fragment_day1_0][@<code>{layout/mine_fragment_day1_0.xml}]{
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:tools="http://schemas.android.com/tools"
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  android:paddingBottom="@dimen/activity_vertical_margin"
  android:paddingLeft="@dimen/activity_horizontal_margin"
  android:paddingRight="@dimen/activity_horizontal_margin"
  android:paddingTop="@dimen/activity_vertical_margin"
  tools:context="com.example.training.MainActivity$PlaceholderFragment" >

  <TextView
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/hello_world" />

</RelativeLayout>
//}

=== レイアウト

 * 家具のレイアウトなどと同じ感じで、レイアウトを指定するとAndroid OS本体が勝手によしなにしてくれる仕組みがある
 ** 個々のパーツを「ウィジェット」などと呼んだりすることがある。覚えなくて良い
 * 「レイアウトエディタ」 ... 「レイアウト」を編集するツール (復習: 「エディタ」)
 * @<code>{AndroidManifest.xml}に続いて、XML形式のファイルを再びいじります

=== @<code>{res/layout/} 下のレイアウトファイル

 * 既出の@<code>{res/layout} の下にレイアウト設定ファイルがある
 * レイアウト設定ファイルに「部品」を配置する
 * 「部品」（パーツ）は「ウィジェット」とか@<code>{View}と呼ばれる
 ** @<code>{View} ... 「見える何か」
 ** 実際には、レイアウト中の全ての部品(「ウィジェット」)は@<code>{View}を「継承」している
 * 今回扱う部品は3種類（全て@<code>{View}を「継承」している）
 ** @<code>{LinearLayout} ... 横並び、縦並びに配置する
 *** Linear: 「直線の」「まっすぐ」
 *** 「リニアモーターカー」のリニア
 ** @<code>{Button} ... ユーザが押せるボタンを配置する
 *** 今回の8x8のマス目を構成する
 ** @<code>{TextView} ... 文字列を表示する
 *** メッセージの表示に使える
 * 関係するレイアウト
 ** @<code>{RelativeLayout} ... 「相対位置」を指定するもの
 *** 今回は使用しない
 ** どう配置するかをXMLで指定する
 *** XML ... Extensible Markup Language
 *** とりあえず「設定ファイルで指定する」とでも覚えましょう
 ** 今は「レイアウトエディタ」というものが便利です
 *** また出ました。エディタ
 *** エディタ: 何かを編集するためのソフト
 **** http://ja.wikipedia.org/wiki/%E3%82%A8%E3%83%87%E3%82%A3%E3%82%BF

==== RelativeLayoutをLinearLayoutに置き換える

 * 今回は@<code>{RelativeLayout}は使いません
 * @<code>{LinearLayout}にとりあえず変更します。
 ** 「横に並べる」「縦に並べる」だけであればこちらの方がはるかに楽なため


==== ボタンを配置する

（チェックポイント: MainActivityDay1_1_Show1Button.java）

 * @<code>{TextView}を@<code>{Button}へ変更する
 * このボタン大きすぎね？
 ** レイアウトエディタで遊んでみましょう
 * テキストを編集してみます。

===== 開発Tips: 「エラー」と「警告」に注意

 * (多分ミスるが、ミスっていなかったらここで@<code>{LinearLayout}のタイポなどをやってみる -> エラー)
 * (同様に、@<code>{@string/hello_world} を別の文字列に変えてしまう -> 警告)
 * ソースコードを「コンパイル」「ビルド」してアプリを作りますが
 ** 「エラー」: 「そ　れ　で　は　う　ご　き　ま　せ　ん」
 ** 「警告」: 「こんなことやってると、後で痛い目見るよ」
 * (デモ: 全角スペースをレイアウトに入れると謎のエラー)
 * エラー: 要は「それは、間違っている」
 ** プログラムはコンピュータから見た時に「厳密」である必要がある
 *** 空気読んでくれない
 *** ぶっちゃけると「出来る事ならば空気を読ませたくない」ものでもある
 ** 挙動はプログラム言語の「仕様」に記載されている
 * 警告の例: strings.xml を使わない
 ** これは「エラー」とは違う

==== ボタンを8つ並べる (MainActivityDay1_2_Show8Buttons.java)

 * 8つ並べます
 * ええと……縦にも並べたい……

==== マインスイーパ風にボタンを 8x8 に並べる (MainActivityDay1_3_Show88Buttons.java)

 * え、どうやってやるの
 * 一歩下がって「どうやって実現するか」を想像する -> 想像した方法がどう実現できるかを調べる
 * 「慌てるな、俺はマインスイーパの8x8の盤面を作りたいだけなんだ」
 * @<code>{LinearLayout} をもう一度考えてみよう
 ** @<code>{LinearLayout} ... 横並び、縦並びに配置してください
 * @<code>{LinearLayout} は別の@<code>{LinearLayout}を並べるのにも使えます！
 ** ボタンを8つ持つ@<code>{LinearLayout}を並べればいい
 * トップレベルのパーツ(「ウィジェット」)には特別な意味が色々あります
 ** 説明は省略しますが……
 ** ここでは「注意して」レイアウトを重ねてみましょう
 ** 説明を省略する事項
 *** match_parent, wrap_content
 * orientation... ？(´・ω・`)
 ** orientation ... 方向
 *** 新歓オリエンテーションとは関係がありません (同じ単語ですが)
 *** 英単語としては「方向を定める」といった感じのニュアンスです
 * @<code>{LinearLayout} をもう一度考えてみよう
 ** @<code>{LinearLayout} ... 横並び、縦並びに配置してください
 ** ……どっちよ
 ** 何も指定していない状況では……横並びです！
 * いわゆる「コピペ」作業発生！
 ** idがかぶります
 ** 一般的に「コピペ」は良くないとされます。
 ** 何故？
 *** 重複しては行けない情報が重複する
 *** 意味が分かってないことが多い
 *** 「コピペ」で出来るのならおそらく「自動化」出来る
 **** 素早く作業するのであれば自動化に勝る高速化はない
 * 3分間クッキングよろしく、作っておきました……！

===== ボタンについているidとは……?

 * ボタン一個一個にIDを振ってあります
 * @<code>{@+id/buttonXY}と今回はしました
 ** ボタンの「座標」を意識しています。

//list[table_again][マインスイーパの盤面]{
|| 00 || 10 || 20 || 30 || 40 || 50 || 60 || 70 ||
|| 01 || 11 || 21 || 31 || 41 || 51 || 61 || 71 ||
|| 02 || 12 || 22 || 32 || 42 || 52 || 62 || 72 ||
|| 03 || 13 || 23 || 33 || 43 || 53 || 63 || 73 ||
|| 04 || 14 || 24 || 34 || 44 || 54 || 64 || 74 ||
|| 05 || 15 || 25 || 35 || 45 || 55 || 65 || 75 ||
|| 06 || 16 || 26 || 36 || 46 || 56 || 66 || 76 ||
|| 07 || 17 || 27 || 37 || 47 || 57 || 67 || 77 ||
//}

 * vertical (縦) の @<code>{LinearLayout} の中に horizontal (横) の @<code>{LinearLayout} を入れています
 ** なので、@<code>{Button} のならびは 00, 10, 20, 30 ... となっている
 ** ややこしいので注意

==== 見た目をよりマインスイーパーっぽくする (mine_fragment_day1_4_better_88_buttons.xml)

 * ボタンの見た目がなんかアレですね
 * 「デフォルト」 (標準) のボタンの見栄えが今回のマインスイーパーに合ってないからです
 * 標準のボタンの見栄えを変える必要があります。
 ** 今回は深入りしませんが……結構面倒です
 ** 9 patch とは？ pressed？ focused？ disabled？
 * プログラマーの日常
 ** わからない時には割とオンラインで聞いたりします
 ** http://qiita.com/amedama/items/fb94c9665a6f7a4e7676
 ** https://github.com/dmiyakawa/crop_9patch_space

=== とりあえず「左上のボタン」を押した際に、何か仕事をさせる
==== このままではボタンを押しても何も起こりません

 * ボタンを押した時に、プログラムに「何かしてよ」と命令します。
 * どのボタンが何をするかを決める必要があります
 * 「どのボタン」を決めるのに「ID」(識別子)が必要です
 ** ID ... 同じ番号が割り振られていないことがとても重要 (当たり前だが)
 ** @<code>{@+id/button0} というのはそういうもの

==== イベントとイベントリスナーとは

 * 「何かが起きたとき」の何かをイベントと言う
 ** イベント
 * 「何かが起きたとき」に反応する仕組みを「イベントリスナー」と言う
 ** 卑近な例: ラジオで林原めぐみが話し始めたら勉強をやめてそっちを聞く
 *** 「ラジオで林原めぐみが話し始める」がイベント
 *** 自分がそのイベントの「リスナー」 (そしてラジオのリスナー)
 *** 「勉強をやめてそっちを聞く」はイベントを「聞いて」自分がなにかする
 * 「ボタンを押したとき」もイベント (@<code>{onClick})

==== ボタンに「イベントリスナー」を登録する

マイルストーン @<code>{MainActivityDay1_5_ButtonWithEvents.java}

 * やりたいこと「ボタンが押された時に……とりあえず文字を表示させる」
 ** 本当にやりたいことは「ボタンを押した時に爆弾があるかを判定すること」
 ** 順番にやっていく
 * @<code>{Fragment}が「ボタンを押したよ」という連絡を受け取れるようにする
 * @<code>{OnClickListener} ... ボタン押されたら何か仕事するもの
 ** 「ボタンを押したよ」 ... @<code>{OnClick} イベントと言う
 ** イベント ... 「何かあったよ」という話
 ** on click ... 「ボタンを押したとき」
 * 今はとりあえずログを出力してお茶を濁す
 ** クリックされた時に何か起きていることを示す！
 ** @<code>{android.util.Log} というパッケージがあります
 ** (パッケージ！未出！)


//list[onclick][onClick()ハンドラ]{
        public void onClick(View v) {
            Log.d("test", "Clicked!");
        }
//}

 * @<code>{onClick()} が追加されました
 ** メソッド、関数とは何……
 *** そこだけプログラムが「実行」します。
 *** 言ってみればモーターみたいな「部品」です
 *** 組み合わせます。


あなたはイベントを理解しました。

== このあとやっていくこと

 * 目標: 「マインスイーパを作る」
 * 一日目ではとにかく「動く」ものを作った
 * 紹介した機能は大きく分ければ2つ
  * 「レイアウト」
  * 「イベント」
 * 仕様をもう一度見直す
  * ボタンを押したときに何が起こるのか
  * ゲームの終了条件は
  * リセットボタン？

=== おまけ

 * https://github.com/dmiyakawa/u-i-ha-ru-
 ** @<code>{LinearLayout}と@<code>{Button}だけでお絵かきを試みた
 ** 実用には堪えない
