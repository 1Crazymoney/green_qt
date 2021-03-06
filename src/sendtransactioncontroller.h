#ifndef GREEN_SENDTRANSACTIONCONTROLLER_H
#define GREEN_SENDTRANSACTIONCONTROLLER_H

#include "accountcontroller.h"

#include <QJsonObject>

class Balance;
class Transaction;

class SendTransactionController : public AccountController
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ isValid NOTIFY changed)
    Q_PROPERTY(Balance* balance READ balance WRITE setBalance NOTIFY changed)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY changed)
    Q_PROPERTY(bool sendAll READ sendAll WRITE setSendAll NOTIFY changed)
    Q_PROPERTY(QString amount READ amount WRITE setAmount NOTIFY changed)
    Q_PROPERTY(QString effectiveAmount READ effectiveAmount NOTIFY changed)
    Q_PROPERTY(QString fiatAmount READ fiatAmount WRITE setFiatAmount NOTIFY changed)
    Q_PROPERTY(QString effectiveFiatAmount READ effectiveFiatAmount NOTIFY changed)
    Q_PROPERTY(QString memo READ memo WRITE setMemo NOTIFY changed)
    Q_PROPERTY(int feeRate READ feeRate WRITE setFeeRate NOTIFY changed)
    Q_PROPERTY(bool hasFiatRate READ hasFiatRate NOTIFY changed)
    Q_PROPERTY(QJsonObject transaction READ transaction NOTIFY transactionChanged)

public:
    explicit SendTransactionController(QObject* parent = nullptr);

    bool isValid() const;

    Balance* balance() const;
    void setBalance(Balance* balance);

    QString address() const;
    void setAddress(const QString& address);

    bool sendAll() const;
    void setSendAll(bool send_all);

    QString amount() const { return m_amount; }
    void setAmount(const QString& amount);

    QString effectiveAmount() const { return m_effective_amount; }

    QString fiatAmount() const { return m_fiat_amount; }
    void setFiatAmount(const QString& fiatAmount);

    QString effectiveFiatAmount() const { return m_effective_fiat_amount; }

    QString memo() const;
    void setMemo(const QString& memo);

    qint64 feeRate() const;
    void setFeeRate(qint64 fee_rate);

    bool hasFiatRate() const;

    QJsonObject transaction() const;

public slots:
    void send();

signals:
    void changed();
    void transactionChanged();

private:
    void update();
    void create();

protected:
    bool m_valid{false};
    quint64 m_count{0};
    Balance* m_balance{nullptr};
    QString m_address;
    bool m_send_all{false};
    QString m_amount, m_effective_amount;
    QString m_fiat_amount, m_effective_fiat_amount;
    QString m_memo;
    qint64 m_fee_rate{0};
    QJsonObject m_transaction;

    void setValid(bool valid);
    bool update(const QJsonObject& result) override;
};

class BumpFeeController : public AccountController
{
    Q_OBJECT
    Q_PROPERTY(int feeRate READ feeRate WRITE setFeeRate NOTIFY changed)
    Q_PROPERTY(QJsonObject tx READ tx NOTIFY txChanged)
    QJsonObject m_tx;
    int m_fee_rate{0};
    int m_req{0};
public:
    BumpFeeController(QObject* parent = nullptr);
    int feeRate() const { return m_fee_rate; }
    void setFeeRate(int feeRate);
    Transaction* transaction();
    Q_INVOKABLE void bumpFee();
    bool update(const QJsonObject& result) override;
    QJsonObject tx() const { return m_tx; }

private slots:
    void create();
signals:
    void changed();
    void txChanged(const QJsonObject& tx);
};

#endif // GREEN_SENDTRANSACTIONCONTROLLER_H
