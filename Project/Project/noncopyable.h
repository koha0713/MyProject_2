#pragma once

/**
 * @class NonCopyable
 * @brief コピーを禁止するためのクラス
 *
 * このクラスは、派生クラスのコピーと代入を防ぐために設計。
 * コピーコンストラクタとコピー代入演算子を削除している。
 */
class NonCopyable {
public:
    /**
     * @brief デフォルトコンストラクタ
     */
    NonCopyable() = default;

    /**
     * @brief コピーコンストラクタを削除
     * @details このクラスのオブジェクトのコピーは許可されていないため、コピーコンストラクタは削除する。
     */
    NonCopyable(const NonCopyable&) = delete;

    /**
     * @brief コピー代入演算子を削除
     * @details このクラスのオブジェクトの代入は許可されていないため、コピー代入演算子は削除する。
     */
    NonCopyable& operator=(const NonCopyable&) = delete;
};
