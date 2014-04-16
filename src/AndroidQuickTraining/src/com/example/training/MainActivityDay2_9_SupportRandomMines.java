package com.example.training;

import java.util.Random;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivityDay2_9_SupportRandomMines extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.container, new PlaceholderFragment()).commit();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment implements OnClickListener {
        private static final int NUM_BOMBS = 8;

        private int[][] mButtonIds = new int[8][8];
        private boolean[][] mIsBomb = new boolean[8][8];
        private int mNumBombs = NUM_BOMBS;
        
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
            
            initializeGameState(rootView);

            Button resetButton = (Button) rootView.findViewById(R.id.reset_button);
            resetButton.setOnClickListener(this);
            return rootView;
        }

        @Override
        public void onClick(View v) {
            Button button = (Button) v;
            View rootView = getView();
            if (button.getId() == R.id.reset_button) {
                initializeGameState(rootView);
                return;
            }

            // 関連するidを探します。ちなみに非常に酷い方法です
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

            handleButtonClick(view_x, view_y, rootView, button);

            // もし全てを開ききったら「クリア」状態にする
            // 計算方法:
            // 爆弾の数が mNumBombs なので
            // 開いていないマス目が mNumBombsで、しかもゲームオーバーになっていなかったら「クリア」
            // ゲームオーバーの場合、このメソッド onClick() はここまで処理を実行しないので、
            // 空いているマス目の数とmNumBombsを比較するだけで良い。
            int numOpenCell = 0;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if (TextUtils.isEmpty(
                            ((Button) rootView.findViewById(mButtonIds[x][y])).getText())) {
                        numOpenCell = numOpenCell + 1;
                    }
                }
            }
            if (numOpenCell == mNumBombs) {
                ((TextView) rootView.findViewById(R.id.top_message)).setText(R.string.clear);
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        ((Button)rootView.findViewById(mButtonIds[x][y])).setEnabled(false);
                    }
                }
            }
        }

        private void handleButtonClick(int view_x, int view_y, View rootView, Button button) {
            Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
            if (mIsBomb[view_x][view_y]) {
                button.setText(R.string.bomb);
                button.setTextColor(Color.RED);

                // 全てのボタンを押せなくする
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        ((Button)rootView.findViewById(mButtonIds[x][y])).setEnabled(false);
                    }
                }
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
                button.setText(String.valueOf(numOfBombs));
                
                if (numOfBombs == 0) {
                    for (int y = view_y - 1; y <= view_y + 1; y++) {
                        if (y < 0 || y >= 8) {
                            continue;
                        }
                        for (int x = view_x - 1; x <= view_x + 1; x++) {
                            if (x < 0 || x >= 8) {
                                continue;
                            }
                            Button neighborButton =
                                    (Button) rootView.findViewById(mButtonIds[x][y]);
                            // 「開いている」 == 「文字が書き込まれている」 (今回はそうした)
                            if (TextUtils.isEmpty(neighborButton.getText())) {
                                // このメソッドをさらに呼んでしまう (再帰)
                                handleButtonClick(x, y, rootView, neighborButton);
                            }
                        }
                    }
                }
            }
        }

        private void initializeGameState(View rootView) {
            // 「クリアした」を表示する一番上のTextViewをリセット
            ((TextView) rootView.findViewById(R.id.top_message)).setText(R.string.yukkuri);

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    // 書き込んだ文字を消す
                    Button button = (Button)rootView.findViewById(mButtonIds[x][y]);
                    button.setText("");
                    button.setTextColor(Color.BLACK);
                    button.setEnabled(true);
                }
            }

            // 爆弾を配置する前に、まず全ての設置済みの爆弾を撤去する
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    mIsBomb[x][y] = false;
                }
            }

            // 爆弾をランダムに配置するメソッドを呼び出す。
            setBombRandomly();
            // 爆弾を固定位置に配置するメソッドを呼び出す(デバッグする際に有効にする)
            // setBombManually()
        }

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
            // 手動で設定したボムの数はNUM_BOMBSと異なるのでここで変更する
            mNumBombs = 4;
            mIsBomb[0][0] = true;
            mIsBomb[3][4] = true;
            mIsBomb[5][6] = true;
            mIsBomb[6][2] = true;
        }
    }
}
