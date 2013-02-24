#ifndef _DS_AUX_OPERATOR_H_
#define _DS_AUX_OPERATOR_H_

class DsAuxOperator
{
	public:
		DsAuxOperator();

	public:
		void copyFrameImage();
		void pasteFrameImage();

		void undo();
		void redo();

		void copyFrame();
		void pastFrame();
	private:
		DsData* m_data;
};


#endif /*_DS_AUX_OPERATOR_H_*/

