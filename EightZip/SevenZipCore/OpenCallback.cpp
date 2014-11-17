#include "OpenCallback.h"

#include <cassert>

#include "Exception.h"
#include "IOpenIndicator.h"

using namespace std;
using namespace boost;

namespace SevenZipCore
{
    STDMETHODIMP OpenCallback::SetTotal(
        const UINT64 *numFiles, const UINT64 *numBytes)
    {
        return S_OK;
    }

    STDMETHODIMP OpenCallback::SetCompleted(
        const UINT64 *numFiles, const UINT64 *numBytes)
    {
        return S_OK;
    }

    STDMETHODIMP OpenCallback::CryptoGetTextPassword(BSTR *password)
    {
        if (m_pOpenIndicator)
        {
            if (auto otstrPassword = m_pOpenIndicator->GetPassword())
            {
                *password = SysAllocStringLen(
                    otstrPassword->data(), otstrPassword->size());
                return S_OK;
            }
        }
        return E_ABORT;
    }

    STDMETHODIMP OpenCallback::SetTotal(UINT64 total)
    {
        return S_OK;
    }

    STDMETHODIMP OpenCallback::SetCompleted(const UINT64 *completeValue)
    {
        return S_OK;
    }

}