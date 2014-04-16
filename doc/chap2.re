= 二日目
== 二日目のレイアウトを用いる（@<code>{MainActivityDay2_0_Start.java}）

今日の進行上使いやすいように、一日目のものからレイアウトに若干の変更を加える。


 * 8x8の盤面の上部に「ゆっくりしていってね！」と表示される@<code>{TextView}を設置する。
  * クリア時のメッセージを表示するのに使う。
 * 8x8の盤面の下部に「Retry」ボタンを設置する。
   * 「リセット」を実装するのに使う。
 * 8x8の盤面を「中央揃え」して、上端に大きめの隙間を設ける。
  * 単純に見栄えの問題。

=== 変更方法

 * 手動で編集している場合、特にレイアウトファイルの内容を@<code>{mine_fragment_day2_0.xml}と同様にする。
 * コピーするのが速いが、練習のため手動で行なっても可

以下に@<code>{mine_fragment_day2_0.xml}の変更を含む場所を掲載する。

//list[day0_start_layout][@<code>{mine_fragment_day2_0.xml}の一部]{
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:tools="http://schemas.android.com/tools"
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  android:layout_marginTop="32dp"
  android:gravity="center_horizontal"
  android:orientation="vertical"
  android:paddingBottom="@dimen/activity_vertical_margin"
  android:paddingLeft="@dimen/activity_horizontal_margin"
  android:paddingRight="@dimen/activity_horizontal_margin"
  android:paddingTop="@dimen/activity_vertical_margin"
  tools:context="jp.ascii.training2014.MainActivity$PlaceholderFragment" >

  <TextView
    android:id="@+id/textView1"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/yukkuri"
    android:textAppearance="?android:attr/textAppearanceLarge" />

... (mine_fragment_day1_4_better_88_buttons.xml同様8x8のボタンが並んでいる)

  <Button
    android:id="@+id/reset_button"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/retry" />
</LinearLayout>
//}

なお、二日目において、レイアウトの変更は以降ない。
基本的に@<code>{mine_fragment_day2.xml}を使い続ける。

== これ以降の変更方法

手作業が不必要に多くなるコードを記述させているケースが増える。

特に手作業に寄る入力に興味がなければ、
一日目に説明した@<code>{Activity}の変更を行いつつ、
ステップ毎の@<code>{Activity}の違いを追うことでコードの内容を理解するほうが効率的だろう。

=== コードの違いを表示する「@<code>{diff}ツール」

 * 特にテキストファイルのどの部分が異なるかを調べるツールを一般に「diffツール」（でぃふつーる）と呼ぶ
 ** 最も一般的なコマンドラインツールが@<code>{diff}コマンドという名前であったため
 ** 違いを「差分」と言う（参考: @<href>{http://goo.gl/tNztnx}（差分 - Wikipedia））
 * 現在は図示するツールを使うのがより一般的（例: @<href>{http://meldmerge.org/}）

//image[meld-example][差分ツールの一つ@<code>{Meld}を@<code>{mine_fragment_day1_4_better_88_buttons.xml}と@<code>{mine_fragment_day2.xml}の2ファイルに対して適用した例][]{
//}

== 全てのボタンにイベントリスナーを設定する（@<code>{MainActivityDay2_1_HandlingAllEvents.java})

 * 一日目では「左上のボタン」に対してだけ「イベントリスナー」を登録した。
 * 全部のボタンにイベントを登録するにはどうすれば良いか。

=== @<code>{for}と@<code>{if}を利用して「全てのボタン」に「イベントリスナー」を登録する

 * 8x8 のボタンはどのようにレイアウトファイルに書かれていたか
 ** ルート（根っこ）となる@<code>{LinearLayout}の「子供」に@<code>{LinearLayout}が8個
 ** 「子供」の「子供」(つまり「孫」)にそれぞれ、対象となる@<code>{Button}が8個
 * よって「ルート（根っこ）の子供の子供がボタンだったらイベントを登録する」が今回やること
 * 注意: 「ルート（根っこ）の子供がボタンだったらイベントは登録しない」
 ** ルートの@<code>{LinearLayout}は、二日目には@<code>{TextView}と@<code>{Button}も含んでいる

//list[logd_on_grandchild][「イベントリスナー」を「孫」のボタンに登録する]{
@Override
public View onCreateView(LayoutInflater inflater, ViewGroup container,
    Bundle savedInstanceState) {
  LinearLayout rootView = (LinearLayout)
      inflater.inflate(R.layout.mine_fragment_day2, container, false);
  for (int index=0; index < rootView.getChildCount(); index++) {
    View child = rootView.getChildAt(index);
    if (child instanceof LinearLayout) {
      LinearLayout childAsLinearLayout = (LinearLayout) child;
      for (int index2=0; index2 < childAsLinearLayout.getChildCount(); index2++) {
        View grandchild = childAsLinearLayout.getChildAt(index2);
        if (grandchild instanceof Button) {
            ((Button) grandchild).setOnClickListener(this);
        }
      }
    }
  }
  return rootView;
}

@Override
public void onClick(View v) {
  Log.d("test", "Clicked!");
}
//}

== ボタンのイベントリスナーがX座標、Y座標を得られるようにする（@<code>{MainActivityDay2_2_HandlingAllEventsWithXY.java})

 * "Clicked!"だけでは「どれ」がクリックされたかが分からない。
 ** それがわからないと「爆弾を踏んだか」も分からない
 * 「座標」をログに表示させるにはどうすれば良いか。

=== 今回採用する方法

 * 2次元配列@<code>{mButtonIds}を用意する。
 * @<code>{mButtonIds[X][Y]}に各ボタンのリソースIDの値を登録しておく。
 * クリックがあったら、どのボタンがクリックされたかを@<code>{mButtonIds}全体を見てチェックする

//list[log_with_cordinate][座標を表示する]{
public static class PlaceholderFragment extends Fragment implements OnClickListener {
  private int[][] mButtonIds = new int[8][8];

  public PlaceholderFragment() {
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
        Bundle savedInstanceState) {
    LinearLayout rootView = (LinearLayout)
        inflater.inflate(R.layout.mine_fragment_day2, container, false);
    for (int index=0, y=0; index < rootView.getChildCount(); index++) {
      View child = rootView.getChildAt(index);
      if (child instanceof LinearLayout) {
        LinearLayout childAsLinearLayout = (LinearLayout) child;
        for (int index2=0, x=0; index2 < childAsLinearLayout.getChildCount(); index2++) {
          View grandchild = childAsLinearLayout.getChildAt(index2);
          if (grandchild instanceof Button) {
            ((Button) grandchild).setOnClickListener(this);
            mButtonIds[x][y] = grandchild.getId();
            x++;
          }
        }
        y++;
      }
    }
    return rootView;
  }

  @Override
  public void onClick(View v) {
    boolean found = false;
    int view_x = -1;
    int view_y = -1;
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (mButtonIds[x][y] == v.getId()) {
          found = true;
          view_x = x;
          view_y = y;
          break;
        }
      }
      if (found) {
        break;
      }
    }
    Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
  }
}
//}

==== 改善できないだろうか……？

 * @<code>{mButtonIds}は最悪のケースではクリック1回につき、盤面全てのIDをチェックしようとする
 * 盤面が100x100だったら10,000回、1,000x1,000ならば1,000,000回のチェックが発生する
 * 一般に、NxNの盤面に対してNの2乗チェックが発生する
 * マインスイーパだから許されるが、仮にGoogleのサーバでこの類のプログラミングをやるとどうなるか？
 * 対策の一つ: いわゆる「ハッシュテーブル」と呼ばれるものを使う。

//list[possibly_better_xy][@<code>{MainActivityDay2_2_HandlingAllEventsWithXY2.java}]{
private static class XY {
    public int x;
    public int y;
    public XY(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public static class PlaceholderFragment extends Fragment implements OnClickListener {
  private SparseArray<XY> mButtonIdToXY = new SparseArray<XY>();

  public PlaceholderFragment() {
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
      Bundle savedInstanceState) {
    LinearLayout rootView = (LinearLayout)
            inflater.inflate(R.layout.mine_fragment_day2, container, false);
    for (int index=0, y=0; index < rootView.getChildCount(); index++) {
        View child = rootView.getChildAt(index);
        if (child instanceof LinearLayout) {
            LinearLayout childAsLinearLayout = (LinearLayout) child;
            for (int index2=0, x=0; index2 < childAsLinearLayout.getChildCount(); index2++) {
                View grandchild = childAsLinearLayout.getChildAt(index2);
                if (grandchild instanceof Button) {
                    ((Button) grandchild).setOnClickListener(this);
                    mButtonIdToXY.put(grandchild.getId(), new XY(x, y));
                    x++;
                }
            }
            y++;
        }
    }
    return rootView;
  }

  @Override
  public void onClick(View v) {
    XY xy = mButtonIdToXY.get(v.getId());
    if (xy != null) {
      Log.d("test", "Clicked! x=" + xy.x + ", y=" + xy.y);
    }
  }
}
//}

 * 今回の範囲では速度差は全く感じない可能性が高い
 ** また、実際に適用する場合は「ベンチマーク」を取るべき
 * 改善していないバージョン（@<code>{mButtonIds}を用いる方法）をそのまま使い続ける

== クリックした場所が爆弾なら「爆」、爆弾ではないなら「開」と表示する（@<code>{MainActivityDay2_3_MineWithBombs.java}）
=== まず爆弾の位置を「初期化」する

 * 初期化 = Initialization ... 下準備
 * つまり、爆弾を配置する
 * 爆弾の位置を記憶しておく必要がある（@<code>{mIsBomb}メンバ変数）
 * 爆弾だったら "爆" と表示する
 ** ついでに色も赤くしてみる
 * このステップでは開いたら "開" とだけ表示することにする
 ** 本当は数字が表示される。次ステップ

== 数字のヒントを表示するようにする（@<code>{MainActivityDay2_4_MineWithNumbersWrong.java}）

 * マインスイーパでは数字が出る。
 * 数字は「周囲の爆弾の数」を示している。
 * 爆弾でない場合、その数字をクリック時に表示する

//image[minesweeper2][マインスイーパのプレイ最中の画面（再掲）]{
//}

なお、このステップには意図的に「バグ」が混入されている。
読んでいる最中に気づけるかチャレンジしてみよう。

=== 「周囲の爆弾の数」を表示する「アルゴリズム」を考える

X座標, Y座標とレイアウトを対応させた以下のテーブルを再掲する。

//list[table_again][マインスイーパの盤面をもう一度。X=3, Y=3に注目]{
| 00 | 10 | 20 | 30 | 40 | 50 | 60 | 70 |
| 01 | 11 | 21 | 31 | 41 | 51 | 61 | 71 |
| 02 | 12 | 22 | 32 | 42 | 52 | 62 | 72 |
| 03 | 13 | 23 | @<b>{33} | 43 | 53 | 63 | 73 |
| 04 | 14 | 24 | 34 | 44 | 54 | 64 | 74 |
| 05 | 15 | 25 | 35 | 45 | 55 | 65 | 75 |
| 06 | 16 | 26 | 36 | 46 | 56 | 66 | 76 |
| 07 | 17 | 27 | 37 | 47 | 57 | 67 | 77 |
//}

 * 例えば「33」に注目すると
 ** 22, 32, 42, 23, 43, 24, 34, 35 のボタンが爆弾であるかを確認すればよい
 ** そのマス目の上下左右斜めにある爆弾の合計を調べる……
 ** @<code>{mIsBomb[3][3]}の「上下左右斜め」を見れば良いのではないか……
 * もっと「一般的」に考える
 ** (x, y) として考えると……

//list[bomb_and_you][一般的な座標計算]{
| x-1, y-1 | x, y-1 | x+1, y-1 |
| x-1, y | x, y | x+1, y |
| x-1, y+1 | x, y+1 | x+1, y+1 |
//}

=== とりあえず左上・上・右上……と全部ロジックを並べてしまおう

 * 左上から順に並べていけばいいのではないか！
 * 検索してみたところ@<code>{setText()}というメソッドが見つかったので使ってみる。

//list[logic][全部並べてしまう例（間違っている）]{
  int numOfBombs = 0;
  // 左上 
  if (mIsBomb[view_x-1][view_y-1]) {
      numOfBombs = numOfBombs + 1;
  }
  // 上
  if (mIsBomb[view_x][view_y-1]) {
      numOfBombs = numOfBombs + 1;
  }
  // 右上
  if (mIsBomb[view_x][view_y+1]) {
      numOfBombs = numOfBombs + 1;
  }
  // 左
  if (mIsBomb[view_x-1][view_y]) {
      numOfBombs = numOfBombs + 1;
  }
  // 中央は要らない
  // 右
  if (mIsBomb[view_x+1][view_y]) {
      numOfBombs = numOfBombs + 1;
  }
  // 左下
  if (mIsBomb[view_x-1][view_y+1]) {
      numOfBombs = numOfBombs + 1;
  }
  // 下
  if (mIsBomb[view_x][view_y+1]) {
      numOfBombs = numOfBombs + 1;
  }
  // 右下
  if (mIsBomb[view_x+1][view_y+1]) {
      numOfBombs = numOfBombs + 1;
  }
  ((Button) v).setText(String.valueOf(numOfBombs));
//}

=== 「アプリが落ちる（クラッシュする）」とは

 * アプリが正常でない状態になっている。これ以上アプリを実行し続けられない。
 * 通常、ユーザが毎回見るものはいわゆる「プログラムのバグ」によることが大半
 * 開発者は「何が原因で落ちたのか」を速やかに見つけて修正する

=== というわけで、落ちた理由を調べる

 * 端っこのボタンをクリックすると、クラッシュする
 ** 「境界条件バグ」と呼ぶことがある。
 * 例えばXが0のとき、X-1はいくつになるか -> -1 -> -1 は配列の外側
 * 例えばXが7のとき、X+1はいくつになるか -> 8 -> 8 は配列の外側

== 問題となるコードを修正する（@<code>{MainActivityDay2_5_MineWithNumbersCorrect.java}）

 * 「XとYが0未満、8以上だったら、チェックしない」という実装にする
 ** @<code>{for}を使って(x-1〜x+1, y-1〜y+1)を指定する
 * さらに……実はもっとシンプルにプログラムを書ける
 ** 効率良く書くのもプログラマの仕事

//list[logic2][もう少しまともなロジック]{
  Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
  if (mIsBomb[view_x][view_y]) {
      ((Button) v).setText("爆");
      ((Button) v).setTextColor(Color.RED);
  } else {
      int numOfBombs = 0;
      for (int y = view_y - 1; y <= view_y + 1; y++) {
          if (y < 0 || y >= 8) {
              continue;
          }
          for (int x = view_x - 1; x <= view_x + 1; x++) {
              if (x < 0 || x >= 8) {
                  continue;
              }
              if (mIsBomb[x][y]) {
                  numOfBombs = numOfBombs + 1;
              }
          }
      }

      ((Button) v).setText(String.valueOf(numOfBombs));
  }
//}


== リセットを実装する（@<code>{MainActivityDay2_6_SupportResetButton.java}）

 * リセットボタン（リソースIDは@<code>{reset_button}）にイベントリスナーを登録する
 * リセットが押されたとき、初期化が再度行われるようにする。
 ** 一部の初期化コードを再利用するべく@<code>{initializeGameState()}というメソッドを新たに準備する
 ** 爆弾の配置、既に表示されている「爆」や数字を消す作業も行う。

//list[initialize_game_state][初期化]{
private void initializeGameState(View rootView) {
    // ボタンの状態をリセットします
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // 書き込んだ文字を消します
            ((Button)rootView.findViewById(mButtonIds[x][y])).setText("");
        }
    }
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // ボタンに触れてない
            mIsBomb[x][y] = false;
        }
    }
    mIsBomb[0][0] = true;
    mIsBomb[3][4] = true;
    mIsBomb[5][6] = true;
    mIsBomb[6][2] = true;   
}
//}

=== 爆弾を踏んだらゲーム続行不可能にする

 * 「ゲームオーバー」の処理も実装する
 ** 「ゲームオーバー」時に、ボタンを押せないようにする
 *** @<code>{setEnabled()}, @<code>{isEnabled()}
 *** 初期化時にまた押せるようにするのを忘れないように


== 「完成」を目指す（@<code>{MainActivityDay2_7_SimpleMineSweeper.java}）
=== 自動的に展開する

 * 爆弾が隣り合ってなかったら、隣もクリックしたことにしてしまう
 ** 再帰呼び出し
 ** 本物と多分ちょっと違うが……

=== 全部開いたら「クリアしました！」と表示して動作を止める

 * Resetがあるのでゲームの再開は簡単です

=== 爆弾を「ランダム」で配置する

//list[random_and_fixed][爆弾をランダムで配置する例と固定位置で配置する例]{
public void setBombRandomly() {
    // 自動で設定したボムの数はNUM_BOMBSと一致する
    mNumBombs = NUM_BOMBS;
    Random random = new Random();
    for (int i = 0; i < NUM_BOMBS; i++) {
        while(true) {
            int x = random.nextInt(8);
            int y = random.nextInt(8);
            if (!mIsBomb[x][y]) {
                mIsBomb[x][y] = true;
                break;
            }
        }
    }
    
}

public void setBombManually() {
    // 手動で設定したボムの数はNUM_BOMBSと異なる
    mNumBombs = 4;
    mIsBomb[0][0] = true;
    mIsBomb[3][4] = true;
    mIsBomb[5][6] = true;
    mIsBomb[6][2] = true;            
}
//}

==== 参考: 「ランダム」（「乱数」）を理解するのはとても難しい

 * 本当の意味での「ランダム」というのは「予測不可能」である必要がある
 ** 予測可能だと情報を盗まれたりすることもある
 ** 国家レベルで大事なプロジェクトなら、相当「予測不可能」でないと駄目
 * アルゴリズム「のみ」で「ランダム」は実は作れない
 ** 本当の「乱数」はコンピュータの外部から一部データを引っ張りだしてくる
 * コンピュータの中でアルゴリズムに従って生成されるものは「擬似乱数」と呼ばれる
 ** 一応いくつもある
 * （擬似）乱数を侮った好例: カルドセプトサーガの乱数問題
 ** 参考 @<href>{http://ledyba.org/2006/12/19032902.php}


== 今後の課題: 更にゲームを強化する

 * あくまで入り口だけを紹介
 ** あまりの速度でめまいがしたとしたら、すみません
 * これでは「売り物」にはしづらいかも？
 ** 昔はこれでも売れた

=== 最初のクリックでは爆弾を踏まないように「ランダム」に配置する？

 * これが本家マインスイーパの挙動
 * 理屈は簡単: クリックした時、クリックした位置に爆弾を置かないように初期化する
 * 今回は省略

=== 「爆」ではなく爆弾アイコンを表示する

 * 画像ファイルの扱いを学ぶ必要がある

=== 8x8の固定画面から変更できるようにするには

 * あるいは「数字決め打ちがどれだけ害悪か」
 * これまでの方法だと'''非常にヨロシクない'''ことが分かる
 * 「8」という数字を各所で使いすぎている
 ** 増やすにも……
 * 変数を上手く活用しましょう！

=== 「旗」を立てる

 * マウスと違って「右クリック」がない
 * 長押し？
 ** 最近あまり使われなくなっているらしい

=== クリアまでの所要時間を測る

 * 開始時刻を覚えておき、クリア時に表示する
 * ストップウォッチの常時表示をするには、別の機構が必要
 ** ストップウォッチを随時アップデートする必要がある
 ** 基本的にはボタンと同様「イベントリスナ」を登録し、「イベント」を処理する

=== 「ゲームの中断」をサポートする

 * 今の実装ではゲームをプレイ中、他のアプリ（例: Twitter）を見て、ゲームを再開しようとすると、たまにゲーム画面全体が再初期化されてしまう
 ** 明示的に途中状態を保存しなければならない

=== 色々な端末に最適な見た目にする

 * 骨がおれます。
 * 今回のようにレイアウトを固定にしては「いけません」
 ** サイズに併せてレイアウトを複数用意します。

=== 画面のローテーションに対応する

 * Androidの奥深い世界へようこそ
 * 回転する際に画面を一旦破棄します
 * おおまかにやるべきこと
 ** 状態を覚えておく
 ** 回転が終わった後に状態を復帰する
 * 今回は省略します

=== バグ……バグ……

 * 全体的に今回の実装はかなり手を抜いている
 * 古いデバイスで（多分）動かない
 * Android開発は始まったばかりである、ということ

== 開発に役立つ情報

 * プロフェショナルもアマチュアも同じツール類で開発している
 ** シンセサイザーみたいに何十万もするツールとかは要らない
 *** 例外: 画像やUI関連では色々専門のツールを使うデザイナーがいます
 * アプリ開発にとりあえず必要なものが全て見えてしまっている
 ** 逆に言うと「初級者はめまいがする」
 * たくさんの「設定」を行なって、プログラムも書く。絵も適切な場所に入れる
 ** Androidの流儀、ルールというのがある。
 ** 毎度本家公式ページを見に行く
 * 資料やコミュニケーションは英語が主
 ** 日本人の開発者コミュニティ内であれば日本語を使いますが、開発元は英語でコミュニケーションを行います
 ** 英語がわからないと少なくとも「出遅れます」
 ** 市販の教科書が「間違って」いたりします
 * スマートフォンは非常に進化が速い

=== 参考になるWebサイト等

 * http://developer.android.com/
 * http://android-developers.blogspot.jp/
 * https://groups.google.com/forum/?hl=en#!forum/android-developers

 * http://www.android-group.jp/
 * https://github.com/TechBooster/AndroidOpenTextbook
 ** 教科書を作っています

=== 参考図書

 * 『Androidプログラミング入門 改訂2版』 2012/08/31 初版
