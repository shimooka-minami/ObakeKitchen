/**
 * TaskSchedulerSystem.h
 * タスクスケジューラーシステム
 */
#pragma once


class TaskSchedulerSystem : public Noncopyable
{
      using Callback = std::function<void()>;


        private:
            struct Event
            {
                float triggerTime;      // 実行される目標時刻
                Callback callback;
                float interval;         // ループ用の間隔保持
                bool delayNextFrame;    // 実行条件を満たした後、さらに1フレーム待つか
            };


        private:
            float m_currentTime = 0.0f;
            std::vector<Event> m_events;
            bool m_needsSort = false;
            // ダブルバッファ構造で「次のフレーム」を確実に保証する
            std::vector<Event> m_currentFrameEvents;         // 今のフレームで実行するもの
            std::vector<Event> m_pendingNextFrameEvents;     // 次のフレームに回すもの


        public:
            TaskSchedulerSystem() {}
			~TaskSchedulerSystem() {}
            

            /**
             * タイマーをスケジュールする
             * @param delay 実行までの秒数
             * @param callback 実行される処理
             * @param loop ループするか
             */
            void AddTimer(float delay, Callback callback, bool delayNextFrame = false)
            {
                float targetTime = m_currentTime + delay;
                m_events.push_back({ targetTime, std::move(callback), delay, delayNextFrame });
                m_needsSort = true;
            }

            /**
             * 毎フレームの更新
             * @param deltaTime フレーム経過時間
             */
            void Update(float deltaTime)
            {
                m_currentTime += deltaTime;

                if (m_needsSort) {
                    SortEvents();
                    m_needsSort = false;
                }

                // 実行時刻が来たイベントを処理
                for (auto it = m_events.begin(); it != m_events.end(); ) {
                    if (m_currentTime >= it->triggerTime) {
                        if (it->delayNextFrame) {
                            // 「次のフレームで実行」リストへ移送する
                            m_pendingNextFrameEvents.push_back(std::move(*it));
                        } else {
                            // コールバック実行
                            if (it->callback) {
                                it->callback();
                            }
                        }
                        it = m_events.erase(it);
                    } else {
                        // ソート済みなので、現在の時刻より先の話であればこれ以上回さない
                        break;
                    }
                }

                // 「次フレーム実行」タスクの処理
                // 前回のupdateで「実行待ち」になったものをここで動かす
                std::vector<Event> eventsToExecute;
                eventsToExecute.swap(m_currentFrameEvents); // 前回分を吸い出す

                for (const auto& task : eventsToExecute) {
                    if (task.callback) task.callback();
                }

                // 今回のupdateで発生した「次フレーム待ち」を次回の実行用へ移動
                m_currentFrameEvents.swap(m_pendingNextFrameEvents);
            }

        private:
            void SortEvents()
            {
				// std::vectorのsortを使ってイベントをトリガー時間でソート
                std::sort(m_events.begin(), m_events.end(), [](const Event& a, const Event& b)
                    {
                        return a.triggerTime < b.triggerTime;
                    });
            }
        };