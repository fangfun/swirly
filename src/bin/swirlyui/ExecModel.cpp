/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include "ExecModel.hpp"

#include <algorithm>

using namespace std;

namespace swirly {
namespace ui {
using namespace exec;

ExecModel::ExecModel(QObject* parent) : QAbstractTableModel{parent}
{
  header_[unbox(Column::CheckState)] = tr("");
  header_[unbox(Column::MarketId)] = tr("Market Id");
  header_[unbox(Column::Contr)] = tr("Contr");
  header_[unbox(Column::SettlDate)] = tr("Settl Date");
  header_[unbox(Column::Id)] = tr("Id");
  header_[unbox(Column::OrderId)] = tr("Order Id");
  header_[unbox(Column::Accnt)] = tr("Accnt");
  header_[unbox(Column::Ref)] = tr("Ref");
  header_[unbox(Column::State)] = tr("State");
  header_[unbox(Column::Side)] = tr("Side");
  header_[unbox(Column::Lots)] = tr("Lots");
  header_[unbox(Column::Price)] = tr("Price");
  header_[unbox(Column::Resd)] = tr("Resd");
  header_[unbox(Column::Exec)] = tr("Exec");
  header_[unbox(Column::AvgPrice)] = tr("Avg Price");
  header_[unbox(Column::LastLots)] = tr("Last Lots");
  header_[unbox(Column::LastPrice)] = tr("Last Price");
  header_[unbox(Column::MinLots)] = tr("Min Lots");
  header_[unbox(Column::MatchId)] = tr("Match Id");
  header_[unbox(Column::LiqInd)] = tr("Liq Ind");
  header_[unbox(Column::Cpty)] = tr("Cpty");
  header_[unbox(Column::Created)] = tr("Created");
}

ExecModel::~ExecModel() noexcept = default;

int ExecModel::rowCount(const QModelIndex& parent) const
{
  return rows_.size();
}

int ExecModel::columnCount(const QModelIndex& parent) const
{
  return ColumnCount;
}

QVariant ExecModel::data(const QModelIndex& index, int role) const
{
  QVariant var{};
  if (!index.isValid()) {
    // No-op.
  } else if (role == Qt::CheckStateRole) {
    const auto& row = rowAt(index.row());
    switch (box<Column>(index.column())) {
    case Column::CheckState:
      var = row.checked() ? Qt::Checked : Qt::Unchecked;
      break;
    default:
      break;
    }
  } else if (role == Qt::DisplayRole) {
    const auto& exec = valueAt(index.row());
    switch (box<Column>(index.column())) {
    case Column::CheckState:
      break;
    case Column::MarketId:
      var = toVariant(exec.marketId());
      break;
    case Column::Contr:
      var = exec.contr().mnem();
      break;
    case Column::SettlDate:
      var = exec.settlDate();
      break;
    case Column::Id:
      var = toVariant(exec.id());
      break;
    case Column::OrderId:
      var = toVariant(exec.orderId());
      break;
    case Column::Accnt:
      var = exec.accnt();
      break;
    case Column::Ref:
      var = exec.ref();
      break;
    case Column::State:
      var = enumString(exec.state());
      break;
    case Column::Side:
      var = enumString(exec.side());
      break;
    case Column::Lots:
      var = toVariant(exec.lots());
      break;
    case Column::Price:
      var = ticksToPriceString(exec.ticks(), exec.contr());
      break;
    case Column::Resd:
      var = toVariant(exec.resd());
      break;
    case Column::Exec:
      var = toVariant(exec.exec());
      break;
    case Column::AvgPrice:
      var = ticksToAvgPriceString(exec.exec(), exec.cost(), exec.contr());
      break;
    case Column::LastLots:
      var = toVariant(exec.lastLots());
      break;
    case Column::LastPrice:
      var = ticksToPriceString(exec.lastTicks(), exec.contr());
      break;
    case Column::MinLots:
      var = toVariant(exec.minLots());
      break;
    case Column::MatchId:
      var = toVariant(exec.matchId());
      break;
    case Column::LiqInd:
      var = enumString(exec.liqInd());
      break;
    case Column::Cpty:
      var = exec.cpty();
      break;
    case Column::Created:
      var = exec.created();
      break;
    }
  } else if (role == Qt::TextAlignmentRole) {
    switch (box<Column>(index.column())) {
    case Column::CheckState:
      break;
    case Column::Contr:
    case Column::Accnt:
    case Column::Ref:
    case Column::State:
    case Column::Side:
    case Column::LiqInd:
    case Column::Cpty:
      var = QVariant{Qt::AlignLeft | Qt::AlignVCenter};
      break;
    case Column::MarketId:
    case Column::SettlDate:
    case Column::Id:
    case Column::OrderId:
    case Column::Lots:
    case Column::Price:
    case Column::Resd:
    case Column::Exec:
    case Column::AvgPrice:
    case Column::LastLots:
    case Column::LastPrice:
    case Column::MinLots:
    case Column::MatchId:
    case Column::Created:
      var = QVariant{Qt::AlignRight | Qt::AlignVCenter};
      break;
    }
  } else if (role == Qt::UserRole) {
    var = QVariant::fromValue(valueAt(index.row()));
  }
  return var;
}

QVariant ExecModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  QVariant var{};
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    var = header_[section];
  }
  return var;
}

void ExecModel::updateRow(uint64_t tag, const Exec& exec)
{
  // Linear search is acceptable on small circular buffer.
  auto it = find_if(rows_.begin(), rows_.end(), [&exec](const auto& row) {
    return row.value().marketId() == exec.marketId() && row.value().id() == exec.id();
  });

  if (it != rows_.end()) {
    // Update tag for completeness. Note that this is not strictly necessary because the sweep
    // operation in not supported.
    it->setTag(tag);
    if (isModified(it->value(), exec)) {
      it->setValue(exec);
      const int row = distance(rows_.begin(), it);
      emit dataChanged(index(row, 0), index(row, ColumnCount - 1));
    }
  } else {
    if (rows_.full()) {
      rows_.push_front(Row<Exec>{tag, exec});
      emit dataChanged(index(0, 0), index(rows_.size() - 1, ColumnCount - 1));
    } else {
      beginInsertRows(QModelIndex{}, 0, 0);
      rows_.push_front(Row<Exec>{tag, exec});
      endInsertRows();
    }
  }
}

} // ui
} // swirly
