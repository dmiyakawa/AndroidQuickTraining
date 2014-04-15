= 一日目
== はじめに

 * 目標: 「マインスイーパ」をAndroidアプリとして実装してみる
 * 前提: JavaとEclipseの扱いが少し分かること
 ** Javaで@<code>{if}, @<code>{for}といった概念が分かる。
 *** メソッド等についても書き方が分かる
 ** EclipseとAndroid SDKのインストール、ADTの準備ができている
 ** EclipseでAndroidプロジェクトのインポートが出来ること

=== 「マインスイーパ」とは

 * @<href>{http://goo.gl/yBHU77} (マインスイーパ - Wikipedia)
 * @<href>{http://minesweeperonline.com/#beginner}
 ** 画像を@<img>{minesweeper}に示す。
 * このゲームをAndroid上で動くように作ってみる。

//image[minesweeper][マインスイーパ][]{
//}

=== マインスイーパの「仕様」を考える

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

=== Android上で実装する場合、どのような要素が必要か

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


== サンプルプロジェクトをコンパイルしてアプリを実行する（@<code>{MainActivityDay1_0_Start.java}）

目標（「マインスイーパを作る」）とそれを達成する要素を考慮した上で、
まず最初にサンプルプロジェクトを動作させることから始める。

アプリケーション（アプリ）のプロジェクトは@<code>{src/AndroidQuickTraining} ディレクトリにある。
これをEclipseにインポートする。

 * Eclipseへのインポート方法
  * File -> New -> Project.. を選択
  * Androidフォルダの Android Project from Existing Code を選択
  * Browse ボタンを押し、サンプルプロジェクトのフォルダを選択して OK
  * src/AndroidQuickTraining を選択して Finish
 * 注意: Android 4.4.2とエミュレータ用の仮想デバイスを準備しておくこと
 ** 詳細な説明は省略

//image[sdk-and-virtual-device-manager-mod][SDKマネージャと仮想デバイスマネージャ][]{
//}

 * 実行方法
 ** Run -> Run
 ** プロジェクトフォルダを右クリックでも良い（@<img>{run-as-android-application}）

//image[run-as-android-application][サンプルプロジェクトを実行する][]{
//}


=== 参考: 使用するツールの復習
==== Eclipse

 * @<href>{http://goo.gl/qNvb3J} (統合開発環境 - Wikipedia)
 * 統合開発環境: ソフトウェア開発に必要な複数のツールをまとめたソフトウェア
 ** エディタ: 何かを編集するためのソフト。メモ帳のお化けみたいなもの
 ** コンパイラ: ソースコードから実際のソフトウェアとして動作する実行コードを生成するもの
 ** デバッガ: ぼっこわれた時にどこが壊れたか、どうやって壊れたかを調べる (デバッグ) ためのツール
 * 便利機能がたくさんある -> 技術者はエディタの機能に慣れたり、機能を追加したりもする

==== Android SDK
 * Androidのソフトウェア開発を行うための「ソフトウェア開発キット」

==== ADT Plugin for Eclipse

 * Android Developer Tools
 * Eclipseは色々なソフトウェア開発に使う
 * Android SDKとセットで用意することで「Eclipse上でAndroidアプリの開発を行えるようにする」ツールとなる。

==== エミュレータ

 * パソコンの中でAndroidアプリを試しに実行出来る
 * emulator -> emulate = 模倣する、真似する
 * 色々制約がある
 ** 動作がとても遅い
 ** GPSやカメラといった機構を使いづらい
 ** etc.

 エミュレータは起動しっぱなしにしておこう

 * エミュレータ自体の起動が非常に遅い。人生は短い
 * なお、実機（本物のAndroid端末）を準備出来れば、直接実行することも可能

=== アプリの構造を一部理解する

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

==== @<code>{AndroidManifest.xml}

 * このアプリ全般に関する情報が記載されている
 ** アプリ名は何か
 ** アイコンに使う画像はどれか
 ** どういうAndroidデバイスにインストールしてもいいのか
 ** 端末のどういう機能を使ってもいいのか（Permission）
 * XML（Extensible Markup Language、「えっくすえむえる」と読む）形式で記述されている
 ** XMLという形式自体はAndroidやスマホとは関係なく一般的に使われる
 ** 後述するレイアウトファイルも全てこの形式で記述する
 ** Webページを記述するHTMLと似ている
 * 「Manifest」
 ** 一般的には「積荷証明書」「声明書」といった意味。
 *** 例1: 選挙公約 election manifest
 *** 例2: 共産党宣言 Communist Manifesto
 * 大統領風の人が「これからこのプログラムについての重要な情報を宣言する！」と言っていると想像する

==== プロジェクトに関わるその他の要素

全ては説明しない

 * @<code>{src/} フォルダ
 ** （分かりづらいが、このアプリプロジェクトの含まれている@<code>{src/}とは別）
 ** ソースコード == javaファイルは個々に収まる
 ** 一般的に、source code の一部を引っ張って"src"としてソースコードを収めることがよくある
 * @<code>{res/} フォルダ
 ** リソース (resource) の略で、画像データや文字列データを保存する
 ** 今回はほとんど扱わないが、デバイスの大きさに合わせて複数の画像データが必要になったりする。
 * @<code>{res/layout/}
 ** @<code>{res/}に含まれるリソースの中でも「レイアウト」と呼ばれるものを保存する。
 ** 使い方は後述する

== ここからの進め方
=== 変更点を手動で入力する方法

理想的には、実際に自分で入力しながらステップ毎のファイルと比較する方法を採ると良い。
その場合は、@<code>{MainActivity.java}と@<code>{fragment_main.xml}の組を用いて演習を行う。

なお、@<code>{AndroidManifest.xml}は、サンプルプロジェクトをインストールした時点で
@<code>{MainActiivty.java}を利用する設定になっている。

//list[default_android_manifest_part][@<code>{AndroidManifest.xml}内で@<code>{Activity}が指定されている箇所]{
<activity
    android:name="com.example.training.MainActivity"
    android:label="@string/app_name" >
  <intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>
</activity>
//}

@<code>{MainActivity.java}も@<code>{fragment_main.xml}を参照する状態になっている。

//list[how_to_change_layout][@<code>{Activity}内でレイアウトが指定されている箇所]{
@Override
public View onCreateView(LayoutInflater inflater, ViewGroup container,
                         Bundle savedInstanceState) {
  View rootView = inflater.inflate(R.layout.mine_fragment_day1_1_show_1_button, container,
      false);
    return rootView;
  }
//}

どうしても先に進めなくなった場合、Eclipse上で各チェックポイントとなる
@<code>{Activity}ファイルを@<code>{AndroidManifest.xml}に指定することで、
該当するステップにおける動作を確認することが出来る。

レイアウトの編集に躓いた場合、@<code>{MainActivity.java}で指定されているレイアウトを、
各ステップのレイアウトファイルに変えてみると良い。

なお、@<code>{MainActivity.java}と@<code>{MainActivityDay1_0_Start.java}は、
サンプルプロジェクトのダウンロード時点では（Javaのクラス名を除いて）一致している。
同様に@<code>{fragment_main.xml}と@<code>{mine_fragment_day1_0.xml}も、
サンプルプロジェクトのダウンロード時点では内容が同じになっている。

=== 変更点をチェックポイント毎に追う方法

@<code>{AndroidManifest.xml}で使用する@<code>{Activity}をチェックポイントの実装に切り替えることで、
本トレーニングの動作をステップごとに確認出来る。
@<code>{android:name=""}のダブルクオート内を適切に変更すること。

（この方法で速習を行う場合、レイアウトファイルの設定を変更する必要はない）

//list[use_day2_0_start][@<code>{AndroidManifest.xml}内で二日目冒頭の@<code>{Activity}を参照する例]{
<activity
    android:name="com.example.training.MainActivityDay2_0_Start"
    android:label="@string/app_name" >
  <intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>
</activity>
//}


=== トレーニング中の注意事項

もちろん「たくさん」あるが、一部を紹介。

==== 「空白」「改行」「全角文字」「大文字・小文字」「l, 1, L」等の違いに注意

特にブログやWord等で文字を入力しているだけのケースでは意識しないが、
プログラミングにおいてはこれらの文字は意味が全く異なる。

 * 特に「全角文字」はプログラム中ではほぼ「エラー」になる
 ** ユーザに表示する文字を入力するケースは例外
 * 1, l, Lといった違いにも注意。ほぼ「エラー」になる
 * おまけ: @<href>{http://ja.wikipedia.org/wiki/Whitespace}
 ** Whitespaceは「空白」に相当する文字の違いで命令を行うプログラミング言語
 ** 真っ白なプログラム: @<href>{http://compsoc.dur.ac.uk/whitespace/count.ws}

==== 「提供元不明のアプリ」

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

==== 参考: プログラマはインデックスを「0から始める」のがお好き

 * index .. 索引
 * 配列の最初の要素をarray[0]（0-origin）とするか、array[1]（1-origin）とするか
 ** 慣習に若干近い……

実は実生活では無意識に両方混ぜて使っている。

//quote{
複数のオリジンが混在する身近な例として、日時があげられる。
年・月・日は1オリジンであるが、時・分・秒は0オリジンである。
（@<href>{http://goo.gl/NMhrsE} オリジン - Wikipedia）
//}

 * origin ... 起源、源泉、先祖、血統、家柄
 ** origin of civilization で「文明の起源」
 * Androidアプリで使われるJava言語では 0-origin。つまり0から始まる
 * 今回は全く関係ないがメモリアドレスに関わる計算をする際の名残？と考えると分かりやすい
 ** addr+0 は先頭 (今ではlst[1]が最初でも不整合は生じない)

サンプルプロジェクトのファイル名でも、1-originと0-originが混ざってしまっている。

== アプリにボタンを1つ配置する（MainActivityDay1_1_Show1Button.java）

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

=== レイアウトとは何か

 * 「どう部品が配置されるか」を指定する
 ** 「家具のレイアウト」とニュアンスは同じ。
 * アプリ内でレイアウトを指定すると、Android OS本体がその指定どおりに部品を表示する
 * 「レイアウトエディタ」 ... 「レイアウト」を編集するツール (復習: 「エディタ」)
 * @<code>{AndroidManifest.xml}に続いて、XML形式のファイルを再び変更する

==== @<code>{res/layout/}について

 * このフォルダの配下にレイアウト設定ファイルがある
 * レイアウト設定ファイルに「部品」を配置する

==== 今回用いるレイアウト用の部品について

 * 個々の「部品」（パーツ）は「ウィジェット」とか@<code>{View}とも呼ばれる
 ** 今回は「部品」とだけ覚えておけば良い
 * @<code>{LinearLayout} ... 横並び、縦並びに配置する
 ** Linear: 「直線の」「まっすぐ」
 *** 「リニアモーターカー」のリニア
 * @<code>{Button} ... ユーザが押せるボタンを配置する
 ** 今回の8x8のマス目を構成する
 * @<code>{TextView} ... 文字列を表示する
 ** メッセージの表示に使える

=== @<code>{LinearLayout}を配置する

@<code>{LinearLayout}を配置するため、
レイアウトを記述したXML（Extensible Markup Language、「えっくすえむえる」と読む）を編集する。

 * @<code>{LinearLayout}にとりあえず変更します。
 ** 「横に並べる」「縦に並べる」だけであればこちらの方がはるかに楽なため
 * （もともとプロジェクトに@<code>{RelativeLayout}は使いません
 * 「レイアウトエディタ」というものが便利です
 ** @<href>{http://goo.gl/wzI058}（エディタ - Wikipedia）

=== ボタン（@<code>{Button}）を配置する

（チェックポイント: MainActivityDay1_1_Show1Button.java）

 * @<code>{TextView}を@<code>{Button}へ変更する
 * このボタン大きすぎね？
 ** レイアウトエディタで遊んでみましょう
 * テキストを編集してみます。

=== 参考: 「エラー」と「警告」に注意

 * 「エラー」: 「そ　れ　で　は　う　ご　き　ま　せ　ん」
 * 「警告」: 「こんなことやってると、後で痛い目見るよ」
 * 例
 ** @<code>{LinearLayout}のタイポを混入 -> エラー
 ** @<code>{@string/hello_world} を別の文字列に変えてしまう -> 警告
 * エラーは直さなければ動作しない
 * 警告は、動作はするものの、推奨されず、意図しない動作をすることが非常に多い
 ** 色々な理由で起こるが、理由なしに無視をしないほうが良い

== ボタン（@<code>{Button}）を8つ並べる (MainActivityDay1_2_Show8Buttons.java)

 * 8つ並べる
 * @<code>{LinearLayout}が「横に並べる」

== ボタンを8x8の格子状に並べる (MainActivityDay1_3_Show88Buttons.java)

8x8の格子状にボタンを配置するには、今度は縦に@<code>{LinearLayout}を並べることになる。

 * 復習: @<code>{LinearLayout} ... 横並び、縦並びに配置してください
 * @<code>{LinearLayout} は別の@<code>{LinearLayout}を並べるのにも使える
 * ボタンを8つ持つ@<code>{LinearLayout}を8つ並べる


 * 注意: レイアウトを記述したXMLのトップレベルの部品（今回は最初の@<code>{LinearLayout}）には特別な意味がある
 ** 注意してレイアウトを重ねること

=== @<code>{LinearLayout}と@<code>{Button}のサイズや意味を変更する

 * XMLの@<code>{<こういうの>}を「タグ」、その中の@<code>{something=""}というのを「属性」と呼ぶ
 ** 参考: @<href>{http://www.atmarkit.co.jp/aig/01xml/attribute.html}
 * 属性を変更することで、「部品」の動作を詳細に記述する
 * 今回把握しておくべき属性
 ** @<code>{android:layout_width}, @<code>{android:layout_height}
 ** @<code>{android:minWidth}, @<code>{android:minWidth}
 ** @<code>{android:orientation}（@<code>{LinearLayout}で使う）
 *** orientation ... 方向
 *** 「横並び」なのか「縦並び」なのかを@<code>{orientation}という属性で指定することが出来る
 *** 「並び」が影響するのは今回は@<code>{LinearLayout}だけ
 *** 何も指定していない状況では横並びになる。
 ** @<code>{android:id} ... 今は各ボタンに重複なく割り当てられていればOK
 *** サンプルプロジェクトでは@<code>{@+id/buttonXY}（X座標とY座標）としている

いわゆる「コピペ」作業を行う

 * idがかぶります
 * 一般的に「コピペ」は良くないとされます。
 * 何故？
 ** 重複しては行けない情報が重複する
 ** 意味が分かってないことが多い
 ** 「コピペ」で出来るのならおそらく「自動化」出来る
 *** 素早く作業するのであれば自動化に勝る高速化はない

@<code>{mine_fragment_day1_3_show_88_buttons.xml}を用いても良い。

==== ボタンについているidとは

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

=== 見た目をよりマインスイーパーっぽくする

（チェックポイント: mine_fragment_day1_4_better_88_buttons.xml）

 * ボタンの見た目がなんかアレですね
 * 「デフォルト」 (標準) のボタンの見栄えが今回のマインスイーパーに合ってないからです
 * 標準のボタンの見栄えを変える必要があります。
 ** 今回は深入りしませんが……結構面倒です
 ** 9 patch とは？ pressed？ focused？ disabled？
 * プログラマーの日常
 ** わからない時には割とオンラインで聞いたりします
 * 今回は自分で用意した「隙間のないボタン用drawable」を使う
 ** 参考1: @<href>{http://qiita.com/amedama/items/fb94c9665a6f7a4e7676}
 ** 参考2: @<href>{https://github.com/dmiyakawa/crop_9patch_space}

== ユーザがボタンを押したとき、アプリを反応させる
=== このままではボタンを押しても何も起こりません

 * ボタンを押した時に、プログラムに「何かしてよ」と命令します。
 * どのボタンが何をするかを決める必要があります
 * 「どのボタン」を決めるのに「ID」(識別子)が必要です
 ** ID ... 同じ番号が割り振られていないことがとても重要 (当たり前だが)
 ** @<code>{@+id/button0} というのはそういうもの

=== イベントとイベントリスナーとは

 * 「何かが起きたとき」の何かをイベントと言う
 ** イベント
 * 「何かが起きたとき」に反応する仕組みを「イベントリスナー」と言う
 ** 卑近な例: ラジオで林原めぐみが話し始めたら勉強をやめてそっちを聞く
 *** 「ラジオで林原めぐみが話し始める」がイベント
 *** 自分がそのイベントの「リスナー」 (そしてラジオのリスナー)
 *** 「勉強をやめてそっちを聞く」はイベントを「聞いて」自分がなにかする
 * 「ボタンを押したとき」もイベント (@<code>{onClick})

=== ボタンに「イベントリスナー」を登録する

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
 ** パッケージ ... Javaの概念。「名前空間」と呼ばれる概念と関係がある
 *** ここでは、ファイルを格納するフォルダ構造と同様なものと考えておく
 *** @<href>{http://goo.gl/idxKQf}（名前空間 - Wikipedia）

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
