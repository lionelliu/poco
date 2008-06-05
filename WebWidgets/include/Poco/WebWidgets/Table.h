//
// Table.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/Table.h#10 $
//
// Library: WebWidgets
// Package: Views
// Module:  Table
//
// Definition of the Table class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef WebWidgets_Table_INCLUDED
#define WebWidgets_Table_INCLUDED


#include "Poco/WebWidgets/View.h"
#include "Poco/WebWidgets/Formatter.h"
#include "Poco/WebWidgets/TableModel.h"
#include "Poco/WebWidgets/TableColumn.h"
#include "Poco/WebWidgets/RequestProcessor.h"
#include "Poco/WebWidgets/JavaScriptEvent.h"
#include "Poco/FIFOEvent.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <vector>


namespace Poco {
namespace WebWidgets {


class WebWidgets_API Table: public View, public RequestProcessor
	/// A Table widget. Uses per default single cell selection.
{
public:
	typedef Poco::AutoPtr<Table> Ptr;
	typedef std::vector<TableColumn::Ptr> TableColumns;

	static const std::string FIELD_COL;
	static const std::string FIELD_ROW;
	static const std::string FIELD_VAL;
	static const std::string FIELD_CNT;
	static const std::string EV_CELLCLICKED;
	static const std::string EV_ROWCLICKED;
	static const std::string EV_CELLVALUECHANGED;
	static const std::string EV_LOADDATA;
	static const std::string EV_AFTERLOAD;
	
	struct WebWidgets_API CellClick
	{
		std::size_t row;
		std::size_t col;
		
		CellClick(std::size_t row, std::size_t col);
	};
	
	struct WebWidgets_API CellValueChange
		/// Data sent with a cellValueChanged event. 
	{
		std::size_t row;
		std::size_t col;
		const Poco::Any oldValue;
		const Poco::Any newValue;
		CellValueChange(std::size_t row, std::size_t col, const Poco::Any& oldValue, const Poco::Any& newValue);
	};
	
	struct LoadData
	{
		Poco::Net::HTTPServerResponse* pResponse;
		Table* pTable;
		int firstRow;
		int rowCnt;
		LoadData(Poco::Net::HTTPServerResponse* pResponse, Table* pTable, int firstRow, int rowCnt);
	};
	
	JavaScriptEvent<std::size_t> rowClicked; /// fires the row clicked event
	
	JavaScriptEvent<Table::CellClick> cellClicked; /// fires the cellClicked event
	
	JavaScriptEvent<Table::CellValueChange> cellValueChanged;
	
	JavaScriptEvent<Table*> afterLoad; // thrown after data was loaded
	
	FIFOEvent<LoadData> beforeLoad; /// thrown whenever a load is requested, internal event to which the TableRenderer must register
	
	enum SelectionModel
		/// The selection model used for the table
	{
		SM_CELL = 0,
		SM_SINGLEROW,
		SM_MULTIROW
	};
		
	
	
	Table(const TableColumns& tc, TableModel::Ptr pModel);
		/// Creates an anonymous Table.
		
	Table(const std::string& name, const TableColumns& tc, TableModel::Ptr pModel);
		/// Creates a Table with the given name.

	std::size_t getColumnCount() const;
		/// Returns the number of columns

	const Poco::Any& getValue(std::size_t row, std::size_t col) const;
		///Returns the value at pos(row, col) or an empty Any if no data is stored there

	std::size_t getRowCount() const;
		/// Returns the total number of rows

	void setValue(const Poco::Any& val, std::size_t row, std::size_t col);
		/// Sets the value at pos(row, col)
		
	void setSelectionModel(SelectionModel sm);
		/// Sets the selectionmodel.
		
	SelectionModel getSelectionModel() const;
		/// Returns the selection model
		
	void clear();
		/// Clears the content of the table

	const Table::TableColumns& getColumns() const;
		/// Returns the columns of the table

	const TableModel& getModel() const;
		/// Returns the table model

	void handleForm(const std::string& field, const std::string& value);
		/// Handles a form field submitted by the client.
	
	void handleAjaxRequest(const Poco::Net::NameValueCollection& args, Poco::Net::HTTPServerResponse& response);
		/// Handles a complete AJAX request submitted by the client.
	
protected:
	Table(const std::string& name, const std::type_info& type, const TableColumns& tc, TableModel::Ptr pModel);
		/// Creates a Table and assigns it the given name.
		
	Table(const std::type_info& type, const TableColumns& tc, TableModel::Ptr pModel);
		/// Creates a Table.
		
	~Table();
		/// Destroys the Table.

	void checkValidConfig();
		/// Checks if the Table is valid
		
private:
	TableModel::Ptr _pModel;
	TableColumns    _columns;
	SelectionModel  _sm;
};


//
// Inlines
//
inline std::size_t Table::getColumnCount() const
{
	return _pModel->getColumnCount();
}


inline const Poco::Any& Table::getValue(std::size_t row, std::size_t col) const
{
	return _pModel->getValue(row, col);
}


inline std::size_t Table::getRowCount() const
{
	return _pModel->getRowCount();
}


inline void Table::clear()
{
	return _pModel->clear();
}


inline const Table::TableColumns& Table::getColumns() const
{
	return _columns;
}


inline const TableModel& Table::getModel() const
{
	return *_pModel;
}


inline void Table::setSelectionModel(Table::SelectionModel sm)
{
	_sm = sm;
}

		
inline Table::SelectionModel Table::getSelectionModel() const
{
	return _sm;
}



} } // namespace Poco::WebWidgets


#endif // WebWidgets_Table_INCLUDED
