void CWndMgr::PutSetItemOpt( CMover* pMover, CItemElem* pItemElem, CEditString* pEdit )
{
	CString strTemp;
	// 2. 세트 아이템의 구성 요소 인가?
	CSetItem* pSetItem	= CSetItemFinder::GetInstance()->GetSetItemByItemId( pItemElem->m_dwItemId );
	if( pSetItem )
	{
		// 해당 세트 아이템의 구성 요소를 모두 출력 하되 장착 된 것과 안된 것을 색으로 구별하여 출력한다.
		BOOL pbEquiped[MAX_HUMAN_PARTS];
		memset( pbEquiped, 0, sizeof(pbEquiped) );
		int nEquiped;
		pMover->GetEquipedSetItem( pSetItem->m_nId, pbEquiped, &nEquiped );
		// 3. 세트아이템 타이틀 출력
		strTemp.Format( "\n%s (%d/%d)", pSetItem->GetString(), pMover->GetEquipedSetItemNumber( pSetItem ), pSetItem->m_nElemSize );
//		pEdit->AddString( strTemp, dwItemColor[g_Option.m_nToolTipText].dwSetName, ESSTY_BOLD );
		pEdit->AddString( strTemp, dwItemColor[g_Option.m_nToolTipText].dwSetName );
		
		for( int i = 0; i < pSetItem->m_nElemSize; i++ )
		{
			ItemProp* pItemProp	= prj.GetItemProp( pSetItem->m_adwItemId[i] );
			if( pItemProp )
			{
				strTemp.Format( "\n %s", pItemProp->szName  );
				if( pbEquiped[i] ) // 장착되어있는 세트 아이템
					pEdit->AddString( strTemp, dwItemColor[g_Option.m_nToolTipText].dwSetItem1 );
				else
					pEdit->AddString( strTemp, dwItemColor[g_Option.m_nToolTipText].dwSetItem0 );
			}
		}
		// 4. 추가 능력치 출력
		ITEMAVAIL itemAvail;
		memset( &itemAvail, 0, sizeof(itemAvail) );
		pSetItem->GetItemAvail( &itemAvail, nEquiped, TRUE );
		for( i = 0; i < itemAvail.nSize; i++ )
		{
			int nDst = (int)itemAvail.anDstParam[i];
			int nAdj = (int)itemAvail.anAdjParam[i];
			
			if( IsDst_Rate(nDst) )
			{
				if( nDst == DST_ATTACKSPEED )
					strTemp.Format( "\n%s: %s% +d%%", prj.GetText(TID_TOOLTIP_SET), FindDstString( nDst ), nAdj / 2 / 10 );	
				else
					strTemp.Format( "\n%s: %s% +d%%", prj.GetText(TID_TOOLTIP_SET), FindDstString( nDst ), nAdj );	
			}
			else
			{
				strTemp.Format( "\n%s: %s +%d", prj.GetText(TID_TOOLTIP_SET), FindDstString( nDst ), nAdj );
			}
			pEdit->AddString( strTemp, dwItemColor[g_Option.m_nToolTipText].dwSetEffect );
		}
	}
}
