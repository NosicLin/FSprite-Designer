#ifndef _DS_AUX_OPERATOR_H_
#define _DS_AUX_OPERATOR_H_

#include "model/DsModel.h"
class DsAuxOperator
{
	public:
		DsAuxOperator();

	public:
		void copyFrameImage();
		void pasteFrameImage();

		void undo();
		void redo();
		bool canUndo();
        bool canRedo();

        void canCopyFrame();
        void copyFrame();

        void canPasteFrame();
        void pasteFrame();

	private:
		DsData* m_data;
};


#endif /*_DS_AUX_OPERATOR_H_*/

